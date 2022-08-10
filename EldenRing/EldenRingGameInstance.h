// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EldenRingGameInstance.generated.h"


struct FPlayerFileDataTable;
struct FMonsterDataTable;
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

	// 데이터 값 얻어오기(이어하기에서 사용?)

	/*
	FString GetPlayerName();
	int GetPlayerHp();
	FString GetPlayerGun();
	int GetPlayerStage();
	float GetPlayerBgmPower();
	void SetPlayerBgmPower(float fBgmPower);
	void SetPlayerDataDefault();
	void SetPlayerStage();
	void SetPlayerGun(FString yourGun);
	*/

	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerType);

	// 몬스터 데이터값 얻어오기
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterPower(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);

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
};
