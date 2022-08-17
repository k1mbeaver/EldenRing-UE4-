// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnOnCollisonStart_AttackDelegate); // ���� ����
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonEnded_AttackDelegate); // ���� ��
DECLARE_MULTICAST_DELEGATE(FEndAttack_AttackDelegate); // ���� ��
DECLARE_MULTICAST_DELEGATE(FGameStart_IntroDelegate); // ���� ��Ʈ�� ��

/**
 * 
 */
UCLASS()
class ELDENRING_API UMonsterInstance : public UAnimInstance
{
	GENERATED_BODY()

		UMonsterInstance();
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		virtual void NativeBeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Intro, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IntroMontage;

	FName GetAttackMontageSectionName(int32 Section);
	void SetDeadAnim();

private:
	UFUNCTION()
		void AnimNotify_OnAttackStart();
	UFUNCTION()
		void AnimNotify_OnAttackEnded();
	UFUNCTION()
		void AnimNotify_EndAttack();
	UFUNCTION()
		void AnimNotify_StartGame();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance�� ����ؼ� C++ ��ũ���� �� ���� �������Ʈ���� ����� �����ϴ�.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	int nMonsterType;

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsIntro;

	FOnOnCollisonStart_AttackDelegate OnOnCollisonStart_Attack;
	FOnOnCollisonEnded_AttackDelegate OnOnCollisonEnd_Attack;
	FEndAttack_AttackDelegate EndAttack_Attack;
	FGameStart_IntroDelegate StartGame_Intro;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void PlayIntroMontage(UAnimMontage* GetIntroMontage);
};
