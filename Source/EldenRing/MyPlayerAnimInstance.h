// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FSaveAttack_AttackDelegate); // 공격 시작
DECLARE_MULTICAST_DELEGATE(FResetCombo_AttackDelegate); // 공격 끝
DECLARE_MULTICAST_DELEGATE(FStopIntro_AttackDelegate); // 스킬인트로 끝
DECLARE_MULTICAST_DELEGATE(FEndSKill_AttackDelegate); // 스킬 끝
DECLARE_MULTICAST_DELEGATE(FTravelMode_StartDelegate); // TravelModeStart 끝
DECLARE_MULTICAST_DELEGATE(FTravelMode_EndDelegate); // TravelModeEnd 끝
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonStart_AttackDelegate); // 공격 시작
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonEnded_AttackDelegate); // 공격 끝

/**
 * 
 */
UCLASS()
class ELDENRING_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlaySkillMontage();
	void PlaySkillIntroMontage();
	void PlayTravelStartMontage();
	void PlayTravelEndMontage();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeA;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeB;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeC;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeD;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageSkill;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageSkillIntro;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StartTravelMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* EndTravelMode;

	FName GetAttackMontageSectionName(int32 Section);
	void SetDeadAnim();

	FSaveAttack_AttackDelegate SaveAttack_Attack;
	FResetCombo_AttackDelegate ResetCombo_Attack;
	FEndSKill_AttackDelegate EndSkill_Attack;
	FStopIntro_AttackDelegate StopIntro_Attack;
	FTravelMode_StartDelegate Start_Travel;
	FTravelMode_EndDelegate End_Travel;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance를 사용해서 C++ 스크립팅 한 것을 블루프린트에서 사용이 가능하다.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsTravel;

	int nCombo;

	UFUNCTION()
		void AnimNotify_SaveAttack();
	UFUNCTION()
		void AnimNotify_ResetCombo();
	UFUNCTION()
		void AnimNotify_EndSkill();
	UFUNCTION()
		void AnimNotify_StopIntro();
	UFUNCTION()
		void AnimNotify_Travel_Start();
	UFUNCTION()
		void AnimNotify_Travel_End();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsCanMove;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float fDirection; // AnimInstance를 사용해서 C++ 스크립팅 한 것을 블루프린트에서 사용이 가능하다.
};
