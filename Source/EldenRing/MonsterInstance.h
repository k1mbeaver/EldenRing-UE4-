// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnOnCollisonStart_AttackDelegate); // ���� ����
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonEnded_AttackDelegate); // ���� ��
DECLARE_MULTICAST_DELEGATE(FEndAttack_AttackDelegate); // ���� ��
DECLARE_MULTICAST_DELEGATE(FGameStart_IntroDelegate); // ���� ��Ʈ�� ��
DECLARE_MULTICAST_DELEGATE(FEndSkill_SkillDelegate); // ��ų ��� ��
DECLARE_MULTICAST_DELEGATE(FStartParticle_ParticleDelegate); // Attack ��ƼŬ ����
DECLARE_MULTICAST_DELEGATE(FPlayParticleEffect_ParticleDelegate); // Intro ��ƼŬ ����
DECLARE_MULTICAST_DELEGATE(FStartSkillParticle_ParticleDelegate); // Intro ��ƼŬ ����

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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SkillMontage;

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

	UFUNCTION()
		void AnimNotify_EndSkill();

	UFUNCTION()
		void AnimNotify_StartParticle();

	UFUNCTION()
		void AnimNotify_PlayParticleEffect();

	UFUNCTION()
		void AnimNotify_StartSkillParticle();

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

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsSkill;

	FOnOnCollisonStart_AttackDelegate OnOnCollisonStart_Attack;
	FOnOnCollisonEnded_AttackDelegate OnOnCollisonEnd_Attack;
	FEndAttack_AttackDelegate EndAttack_Attack;
	FGameStart_IntroDelegate StartGame_Intro;
	FEndSkill_SkillDelegate EndSkill_Skill;
	FStartParticle_ParticleDelegate StartParticle_Particle;
	FPlayParticleEffect_ParticleDelegate PlayParticleEffect_Particle;
	FStartSkillParticle_ParticleDelegate StartSkillParticle_Particle;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void PlayIntroMontage(UAnimMontage* GetIntroMontage);
	void PlaySkillMontage(UAnimMontage* GetIntroMontage);
};
