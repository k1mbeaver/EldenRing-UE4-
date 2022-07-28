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


	SpringArm->bUsePawnControlRotation = true; // LookUp�� ����
	//Camera->bUsePawnControlRotation = true;

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_EASYMODEL(TEXT("/Game/File/Mesh/Murdock.Murdock"));
	//if (SK_EASYMODEL.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(SK_EASYMODEL.Object);
	//}

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> PLAYER_START(TEXT("/Game/File/Mesh/Murdock.Murdock"));
	//if (SK_EASYMODEL.Succeeded())
	//{
		//GetMesh()->SetSkeletalMesh(SK_EASYMODEL.Object);
	//}

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrints/Murdock_AnimBlueprint.Murdock_AnimBlueprint_C"));
	//static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrints/Character_AnimBlueprint.Character_AnimBlueprint_C"));
	//if (PLAYER_ANIM.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	//}

	// bullet effect
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/SpreadShot/FX/P_SpreadShotImpact_Radial.P_SpreadShotImpact_Radial'"));
	//if (FIRE.Succeeded())
	//{
	//	FireParticle = FIRE.Object;
	//}

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// ĳ���Ͱ� �ڿ������� ȸ���ϰ� 
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
	//myGun = EGunState::BASIC;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//CharacterAnim = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	GetMesh()->SetSkeletalMesh(MyGI->GetPlayerSkeletalMesh("Default"));
	GetCapsuleComponent()->SetRelativeLocation(FVector(-600.0f, 1500.0f, 500.0f));
	//AEldenRingGM* gameMode = Cast<AEldenRingGM>(GetWorld()->GetAuthGameMode());

	//if (gameMode)
	//{
		//gameMode->RestartPlayer(this->GetController());
	//}

	bIsRun = false;// ������ �� �޸��� �������� ���� ��ó
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ĳ���� �̵� �Լ�
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	
	// ĳ���� ���� �Լ�
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// ĳ���� ���� �Լ�
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::OnFire);

	// ĳ���� �޸��� �Լ�
	//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	// ĳ���� ���� �Լ�
	//PlayerInputComponent->BindAction("ReadyFire", IE_Pressed, this, &AMyCharacter::ReadyFire);
	//PlayerInputComponent->BindAction("ReadyFire", IE_Released, this, &AMyCharacter::ResetReadyFire);

	// �÷��̾� �Ͻ����� �Լ�
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
	Super::Jump();
}

void APlayerCharacter::StopJumping()
{
	Super::StopJumping();
}

void APlayerCharacter::Attack()
{
	// ���� �ִϸ��̼� ����
	//CharacterAnim->PlayAttackMontage();

	//auto AnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	//if (nullptr == AnimInstance) return;
}

void APlayerCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed *= 2.5f;
	bIsRun = true;
}

void APlayerCharacter::StopRun()
{
	if (bIsRun)
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

	if (fPlayerHp == 0) // �ǰ� �� ���̸�
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
