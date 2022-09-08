// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EldenRingGameInstance.generated.h"


struct FPlayerFileDataTable;
struct FMonsterDataTable;
struct FMontageDataTable;
struct FPlayerDataTable;
struct FMonsterParticleDataTable;
struct FPlayerMontageDataTable;
struct FImageDataTable;
class UDataTable;

/**
 * 
 */
UCLASS()
class ELDENRING_API UEldenRingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEldenRingGameInstance();

	// �÷��̾� ������ �� ������
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerType);
	float GetPlayerHP();
	float GetPlayerStamina();
	int GetPlayerStage();
	float GetPlayerMP();

	// ���� �����Ͱ� ������
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterPower(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);

	// �ִ� ��Ÿ�� �����Ͱ� ������
	UAnimMontage* GetMontage(FString MontageType);
	UAnimMontage* GetSkillMontage(FString MontageType);
	UAnimMontage* GetStartIntroMontage(FString MontageType);

	// �ִϸ��̼� �����Ͱ� ������
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	// ���� ��ƼŬ ������
	UParticleSystem* GetMonsterAttackParticle(FString MonsterType);
	UParticleSystem* GetMonsterSkillParticle(FString MonsterType);
	UParticleSystem* GetMonsterIntroParticle(FString MonsterType);

	// �÷��̾� ��Ÿ��, �ִϸ��̼� ������
	UAnimMontage* GetPlayerAttackAMontage();
	UAnimMontage* GetPlayerAttackBMontage();
	UAnimMontage* GetPlayerAttackCMontage();
	UAnimMontage* GetPlayerAttackDMontage();
	UAnimMontage* GetPlayerSkillMontage();
	UAnimMontage* GetPlayerSkillIntroMontage();
	UAnimMontage* GetPlayerStunMontage();
	UAnimMontage* GetPlayerStartTravelMontage();
	UAnimMontage* GetPlayerEndTravelMontage();
	TSubclassOf<class UAnimInstance> GetPlayerAnimation();

	// �̹��� ������
	TSoftObjectPtr<UTexture> GetImage(FString ImageType);


	/*
	FString GetMonsterName(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);
	float GetMonsterAttackDamage(FString MonsterType);
	float GetMonsterAttackSpeed(FString MonsterType);
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	*/
	// ��� ������ �� ������
	//USoundWave* GetSoundWaveBGM(FString Title);

	//UPROPERTY()
		//int nMonsterDeath;

	UPROPERTY()
		FString strSkeletalMesh;

	// Json ���� (����� �̻��)
	//void JsonSave();
	//void JsonLoad();

private:
	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FMonsterTable;

	UPROPERTY()
		UDataTable* FMontageTable;

	UPROPERTY()
		UDataTable* FPlayerTable;

	UPROPERTY()
		UDataTable* FMonsterParticleTable;

	UPROPERTY()
		UDataTable* FPlayerMontageTable;

	UPROPERTY()
		UDataTable* FImageTable;
};
