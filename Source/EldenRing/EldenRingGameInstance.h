// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EldenRingGameInstance.generated.h"


struct FPlayerFileDataTable;
struct FMonsterDataTable;
struct FMontageDataTable;
struct FPlayerDataTable;
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

	// 플레이어 데이터 값 얻어오기
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerType);
	float GetPlayerHP();
	float GetPlayerStamina();
	int GetPlayerStage();
	float GetPlayerMP();

	// 몬스터 데이터값 얻어오기
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterPower(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);

	// 애님 몽타주 데이터값 얻어오기
	UAnimMontage* GetMontage(FString MontageType);

	// 애니메이션 데이터값 얻어오기
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	/*
	FString GetMonsterName(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);
	float GetMonsterAttackDamage(FString MonsterType);
	float GetMonsterAttackSpeed(FString MonsterType);
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	*/
	// 브금 데이터 값 얻어오기
	//USoundWave* GetSoundWaveBGM(FString Title);

	//UPROPERTY()
		//int nMonsterDeath;

	UPROPERTY()
		FString strSkeletalMesh;

	// Json 관련 (현재는 미사용)
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
};
