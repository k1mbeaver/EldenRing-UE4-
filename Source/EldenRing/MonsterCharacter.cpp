// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EldenRingGM.h"
#include "EldenRingGameInstance.h"
#include "MonsterController.h"
#include "MonsterInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

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

	ParticleMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	ParticleMuzzleLocation->SetupAttachment(GetCapsuleComponent());
	ParticleMuzzleLocation->SetRelativeLocation(FVector(-80.f, 80.0f, 30.0f));

	IntroParticleMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("IntroMuzzleLocation"));
	IntroParticleMuzzleLocation->SetupAttachment(GetCapsuleComponent());
	IntroParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyCharacter"));

	// bullet effect
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK(TEXT("ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Primary/FX/P_Sevarog_Melee_SucessfulImpact.P_Sevarog_Melee_SucessfulImpact'"));
	//if (ATTACK.Succeeded())
	//{
		//AttackParticle = ATTACK.Object;
	//}

	bCanAttack = true;

	fMaxHp = 100.0f;
	fAIHp = 100.0f;
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	nMonsterType = MyGI->GetPlayerStage();

	
	switch (nMonsterType)
	{
	case 0:
		strMonsterType = "Grux";
		break;
		
	case 1:
		strMonsterType = "Narbash";
		break;

	case 2:
		strMonsterType = "Rampage";
		break;

	case 3:
		strMonsterType = "Sevarog";
		break;
	}
	
	InitializeAI(strMonsterType); // Narbash, Props, Rampage, Sevarog, Grux
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
	if (bCanAttack)
	{
		bCanAttack = false;

		auto AnimInstance = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayAttackMontage(AttackMontage);
	}
}

void AMonsterCharacter::AttackEnd()
{
	bCanAttack = true;
}

void AMonsterCharacter::Skill()
{
	if (bCanAttack)
	{
		bCanAttack = false;

		auto AnimInstance = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlaySkillMontage(SkillMontage);
	}
}

void AMonsterCharacter::SkillEnd()
{
	bCanAttack = true;
}


void AMonsterCharacter::StopAIController()
{
	AMonsterController* AIController = Cast<AMonsterController>(GetController());

	AIController->StopAI();
}

void AMonsterCharacter::InitializeAI(FString MonsterType)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	AttackMontage = MyGI->GetMontage(MonsterType);
	IntroMontage = MyGI->GetStartIntroMontage(MonsterType);
	SkillMontage = MyGI->GetSkillMontage(MonsterType);

	AttackParticle = MyGI->GetMonsterAttackParticle(MonsterType);
	SkillParticle = MyGI->GetMonsterSkillParticle(MonsterType);
	IntroParticle = MyGI->GetMonsterIntroParticle(MonsterType);

	GetMesh()->SetSkeletalMesh(MyGI->GetMonsterSkeletalMesh(MonsterType));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimInstanceClass(MyGI->GetAnimation(MonsterType));

	fMaxHp = MyGI->GetMonsterHp(MonsterType);
	fAIHp = fMaxHp;
	GetCharacterMovement()->MaxWalkSpeed = MyGI->GetMonsterSpeed(MonsterType);
	AttackPower = MyGI->GetMonsterPower(MonsterType);

	MonsterAnim = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
	MonsterAnim->EndAttack_Attack.AddUObject(this, &AMonsterCharacter::AttackEnd);
	MonsterAnim->EndSkill_Skill.AddUObject(this, &AMonsterCharacter::SkillEnd);
	MonsterAnim->StartParticle_Particle.AddUObject(this, &AMonsterCharacter::AttackParticleStart);
	MonsterAnim->PlayParticleEffect_Particle.AddUObject(this, &AMonsterCharacter::IntroParticleStart);
	MonsterAnim->StartSkillParticle_Particle.AddUObject(this, &AMonsterCharacter::SkillParticleStart);

	// 인트로 모션 시작
	MonsterAnim->PlayIntroMontage(IntroMontage);
}

void AMonsterCharacter::AttackParticleStart()
{
	GameStatic->SpawnEmitterAttached(AttackParticle, ParticleMuzzleLocation, FName("ParticleMuzzleLocation"));
}

void AMonsterCharacter::IntroParticleStart()
{
	GameStatic->SpawnEmitterAttached(IntroParticle, IntroParticleMuzzleLocation, FName("IntroParticleMuzzleLocation"));
}

void AMonsterCharacter::SkillParticleStart()
{
	GameStatic->SpawnEmitterAttached(SkillParticle, ParticleMuzzleLocation, FName("ParticleMuzzleLocation"));
}