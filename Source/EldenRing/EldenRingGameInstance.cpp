// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenRingGameInstance.h"
#include "PlayerFileDataTableClass.h"
#include "MonsterDataTableClass.h"
#include "MontageDataTableClass.h"

UEldenRingGameInstance::UEldenRingGameInstance()
{
	FString PlayerDataPath = TEXT("DataTable'/Game/DataTable/PlayerFileData.PlayerFileData'");
	FString MonsterDataPath = TEXT("DataTable'/Game/DataTable/MonsterData.MonsterData'");
	FString MontageDataPath = TEXT("DataTable'/Game/DataTable/MontageData.MontageData'");

	//E:/Unreal/ZombieShooting/Content/File/Json/PlayerData.uasset
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYER(*PlayerDataPath);

	if (DT_ABPLAYER.Succeeded())
	{
		FPlayerFileTable = DT_ABPLAYER.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABMONSTER(*MonsterDataPath);

	if (DT_ABMONSTER.Succeeded())
	{
		FMonsterTable = DT_ABMONSTER.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABMONTAGE(*MontageDataPath);

	if (DT_ABMONTAGE.Succeeded())
	{
		FMontageTable = DT_ABMONTAGE.Object;
	}
}

USkeletalMesh* UEldenRingGameInstance::GetPlayerSkeletalMesh(FString PlayerType)
{
	FPlayerFileDataTable* SkeletalMeshData = FPlayerFileTable->FindRow<FPlayerFileDataTable>(*PlayerType, TEXT(""));
	USkeletalMesh* PlayerSkeletalMesh = SkeletalMeshData->PlayerMesh;
	return PlayerSkeletalMesh;
}

USkeletalMesh* UEldenRingGameInstance::GetMonsterSkeletalMesh(FString MonsterType)
{
	FMonsterDataTable* SkeletalMeshData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	USkeletalMesh* MonsterSkeletalMesh = SkeletalMeshData->MonsterMesh;
	return MonsterSkeletalMesh;
}

float UEldenRingGameInstance::GetMonsterHp(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterHp = MonsterData->MonsterHp;
	return MonsterHp;
}

float UEldenRingGameInstance::GetMonsterSpeed(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterSpeed = MonsterData->MonsterSpeed;
	return MonsterSpeed;
}

float UEldenRingGameInstance::GetMonsterPower(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterPower = MonsterData->MonsterPower;
	return MonsterPower;
}

UAnimMontage* UEldenRingGameInstance::GetMontage(FString MontageType)
{
	FMontageDataTable* MontageData = FMontageTable->FindRow<FMontageDataTable>(*MontageType, TEXT(""));
	UAnimMontage* myMontage = MontageData->MyMontage;
	return myMontage;
}

TSubclassOf<class UAnimInstance> UEldenRingGameInstance::GetAnimation(FString AnimationType)
{
	FMontageDataTable* AnimationData = FMontageTable->FindRow<FMontageDataTable>(*AnimationType, TEXT(""));
	TSubclassOf<class UAnimInstance> myAnimation = AnimationData->MyAnimation;
	return myAnimation;
}