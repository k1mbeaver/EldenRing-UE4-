// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EldenRingGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMonsterInstance::UMonsterInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/PrimaryAttack_FourStrikes_Montage.PrimaryAttack_FourStrikes_Montage'"));
	//if (ATTACK_MONTAGE.Succeeded())
	//{
		//AttackMontage = ATTACK_MONTAGE.Object;
	//}
}

void UMonsterInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰에 접근해서 폰의 속력 값을 얻어온다.
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UMonsterInstance::PlayAttackMontage()
{
	UEldenRingGameInstance* MyGI = GetWorld()->GetGameInstance<UEldenRingGameInstance>();
	Montage_Play(MyGI->GetMontage("Narbash"), 1.0f);
}

void UMonsterInstance::SetDeadAnim()
{
	IsDead = true;
}

FName UMonsterInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UMonsterInstance::AnimNotify_OnAttackStart()
{
	OnOnCollisonStart_Attack.Broadcast();
}

void UMonsterInstance::AnimNotify_OnAttackEnded()
{
	OnOnCollisonEnd_Attack.Broadcast();
}
