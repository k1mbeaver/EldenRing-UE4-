// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenRingGameInstance.h"
#include "PlayerFileDataTableClass.h"

UEldenRingGameInstance::UEldenRingGameInstance()
{
	FString PlayerDataPath = TEXT("DataTable'/Game/DataTable/PlayerFileData.PlayerFileData'");

	//E:/Unreal/ZombieShooting/Content/File/Json/PlayerData.uasset
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYER(*PlayerDataPath);

	if (DT_ABPLAYER.Succeeded())
	{
		FPlayerFileTable = DT_ABPLAYER.Object;
	}
}

USkeletalMesh* UEldenRingGameInstance::GetPlayerSkeletalMesh(FString PlayerType)
{
	FPlayerFileDataTable* SkeletalMeshData = FPlayerFileTable->FindRow<FPlayerFileDataTable>(*PlayerType, TEXT(""));
	USkeletalMesh* PlayerSkeletalMesh = SkeletalMeshData->PlayerMesh;
	return PlayerSkeletalMesh;
}