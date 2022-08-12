// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EldenRingGM.h"
#include "EldenRingGameInstance.h"
#include "MonsterController.h"
#include "MonsterInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrint/GruxAnimation_BP.GruxAnimation_BP_C"));
	//if (PLAYER_ANIM.Succeeded())
	//{
		//GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
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
	fAIHp = 100.0f;

	IsAttacking = false;
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeAI("Narbash"); // Narbash, Props, Rampage, Sevarog, Grux
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterCharacter::Attack()
{
	auto AnimInstance = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayAttackMontage();
}


void AMonsterCharacter::StopAIController()
{
	AMonsterController* AIController = Cast<AMonsterController>(GetController());

	AIController->StopAI();
}

void AMonsterCharacter::InitializeAI(FString MonsterType)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	//MyAnim = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInstance->OnMontageEnded.AddDynamic(this, APlayerCharacter::OnSkillMontageEnded);
	GetMesh()->SetSkeletalMesh(MyGI->GetMonsterSkeletalMesh(MonsterType));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimInstanceClass(MyGI->GetAnimation(MonsterType));
	fMaxHp = MyGI->GetMonsterHp(MonsterType);
	fAIHp = fMaxHp;
	GetCharacterMovement()->MaxWalkSpeed = MyGI->GetMonsterSpeed(MonsterType);
	AttackPower = MyGI->GetMonsterPower(MonsterType);
}
