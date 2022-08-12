// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "EldenRingGameInstance.h"
#include "MyPlayerAnimInstance.h"
#include "EldenRingGM.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-55.0f, 0.0f, 50.0f));


	SpringArm->bUsePawnControlRotation = true; // LookUp을 위함
	//Camera->bUsePawnControlRotation = true;


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrint/MyPlayerAnimation_BP.MyPlayerAnimation_BP_C"));
	if (PLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}

	// bullet effect
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/SpreadShot/FX/P_SpreadShotImpact_Radial.P_SpreadShotImpact_Radial'"));
	//if (FIRE.Succeeded())
	//{
	//	FireParticle = FIRE.Object;
	//}

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyCharacter"));

	IsAttacking = false;

	fMaxHp = 100.0f;
	fPlayerHp = 100.0f;

	//nSpecialGunBullet = 30;

	bIsRun = false;
	bPlayerPause = false;
	bCanMove = true;
	bIsPlayerControlled = false;
	IsAttacking = false;
	//myGun = EGunState::BASIC;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	GetMesh()->SetSkeletalMesh(MyGI->GetPlayerSkeletalMesh("Default"));

	PlayerAnim = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInstance->OnMontageEnded.AddDynamic(this, APlayerCharacter::OnSkillMontageEnded);

	//PlayerAnim->OnMontageEnded.AddDynamic(this, &APlayerCharacter::OnSkillMontageEnded);
	PlayerAnim->EndSkill_Attack.AddUObject(this, &APlayerCharacter::StopSkill);
	PlayerAnim->StopIntro_Attack.AddUObject(this, &APlayerCharacter::StopIntro);
	bIsRun = false;// 시작할 때 달리기 느려지는 오류 대처
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 캐릭터 이동 함수
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	
	// 캐릭터 점프 함수
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// 캐릭터 공격 함수
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::OnFire);

	// 캐릭터 달리기 함수
	//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	// 캐릭터 견착 함수
	//PlayerInputComponent->BindAction("ReadyFire", IE_Pressed, this, &AMyCharacter::ReadyFire);
	//PlayerInputComponent->BindAction("ReadyFire", IE_Released, this, &AMyCharacter::ResetReadyFire);

	// 플레이어 일시정지 함수
	//PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PlayerPause);
	
}

void APlayerCharacter::UpDown(float NewAxisValue)
{
	if (bCanMove)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		Direction.Z = 0.0f;
		Direction.Normalize();
		AddMovementInput(Direction, NewAxisValue);
	}
}

void APlayerCharacter::LeftRight(float NewAxisValue)
{
	if (bCanMove)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
		Direction.Z = 0.0f;
		Direction.Normalize();
		AddMovementInput(Direction, NewAxisValue);
	}
}

void APlayerCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void APlayerCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void APlayerCharacter::Jump()
{
	if (bCanMove)
	{
		Super::Jump();
	}
}

void APlayerCharacter::StopJumping()
{
	if (bCanMove)
	{
		Super::StopJumping();
	}
}

void APlayerCharacter::Attack()
{
	// 공격 애니메이션 실행
	//CharacterAnim->PlayAttackMontage();
	if (bCanMove)
	{
		IsAttacking = true;

		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayAttackMontage();

		//MyAnim->PlayAttackMontage();
	}
}

void APlayerCharacter::Skill()
{
	// 공격 애니메이션 실행
	//CharacterAnim->PlayAttackMontage();

	bCanMove = false;

	auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlaySkillIntroMontage();

	IsAttacking = true;
	bSkill = true;
}

void APlayerCharacter::StopSkillIntro()
{
	if (IsAttacking)
	{
		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlaySkillMontage();
		PlayerAnim->PlaySkillMontage();
	}
}

void APlayerCharacter::StopSkill()
{
	bCanMove = true;
	IsAttacking = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::StopIntro()
{
	bCanMove = true;
	IsAttacking = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::OnSkillMontageEnded(UAnimMontage* montage, bool Interrupted)
{
	bCanMove = true;
}

void APlayerCharacter::Run()
{
	if (bCanMove)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 2.5f;
		bIsRun = true;
	}
}

void APlayerCharacter::StopRun()
{
	if (bIsRun && bCanMove)
	{
		GetCharacterMovement()->MaxWalkSpeed /= 2.5f;
	}
}

/*
void APlayerCharacter::PlayerPause()
{
	//APlayerInterface_HUD* HUD = Cast<APlayerInterface_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	GameStatic->SetGamePaused(GetWorld(), true);

	FInputModeUIOnly InputMode;
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	//HUD->SetGamePauseUIVisible();
}
*/
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	fPlayerHp -= FinalDamage;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack!"));

	//APlayerInterface_HUD* HUD = Cast<APlayerInterface_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	float fCurrentHP = fPlayerHp / fMaxHp;

	//HUD->SetPlayerHP(fCurrentHP);

	if (fPlayerHp == 0) // 피가 다 까이면
	{
		//CharacterAnim->SetDeadAnim();

		bCanMove = false;

		FInputModeUIOnly InputMode;
		UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

		//HUD->SetGameOverUIVisible();
	}

	//MyTakeDamage.Broadcast();
	return FinalDamage;

}

