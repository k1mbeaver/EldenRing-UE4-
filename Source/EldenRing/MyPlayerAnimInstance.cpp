// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyPlayerAnimInstance::UMyPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = true;
	nCombo = 0;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_A_Slow_Montage.PrimaryAttack_A_Slow_Montage'"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		AttackMontageTypeA = ATTACK_MONTAGE1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_B_Slow_Montage.PrimaryAttack_B_Slow_Montage'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		AttackMontageTypeB = ATTACK_MONTAGE2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE3(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_C_Slow_Montage.PrimaryAttack_C_Slow_Montage'"));
	if (ATTACK_MONTAGE3.Succeeded())
	{
		AttackMontageTypeC = ATTACK_MONTAGE3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE4(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_D_Slow_Montage.PrimaryAttack_D_Slow_Montage'"));
	if (ATTACK_MONTAGE4.Succeeded())
	{
		AttackMontageTypeD = ATTACK_MONTAGE4.Object;
	}
}

void UMyPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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

void UMyPlayerAnimInstance::PlayAttackMontage()
{
	if (IsAttacking == true)
	{
		IsAttacking = false;
		if (nCombo == 0)
		{
			Montage_Play(AttackMontageTypeA, 1.0f);
		}

		else if (nCombo == 1)
		{
			Montage_Play(AttackMontageTypeB, 1.0f);
		}

		else if (nCombo == 2)
		{
			Montage_Play(AttackMontageTypeC, 1.0f);
		}

		else if (nCombo == 3)
		{
			Montage_Play(AttackMontageTypeD, 1.0f);
		}
	}
}

void UMyPlayerAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

FName UMyPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UMyPlayerAnimInstance::AnimNotify_SaveAttack()
{
	SaveAttack_Attack.Broadcast();
	IsAttacking = true;
	nCombo++;
}

void UMyPlayerAnimInstance::AnimNotify_ResetCombo()
{
	ResetCombo_Attack.Broadcast();
	nCombo = 0;
	IsAttacking = true;
}
