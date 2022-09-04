// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_HUD.h"
#include "PlayerUIMain_UW.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

APlayerUI_HUD::APlayerUI_HUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerUIMain_UW> WB_Main(TEXT("WidgetBlueprint'/Game/UI/PlayerUIMain_WB'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerUI_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

bool APlayerUI_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool APlayerUI_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerUIMain_UW>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}

void APlayerUI_HUD::SetPlayerHP(float fCurrent)
{
	MainUIObject->SetPlayerHP(fCurrent);
}

void APlayerUI_HUD::SetPlayerMP(float fCurrent)
{
	MainUIObject->SetPlayerMP(fCurrent);
}

void APlayerUI_HUD::SetPlayerStamina(float fCurrent)
{
	MainUIObject->SetPlayerStamina(fCurrent);
}

void APlayerUI_HUD::SetMonsterHP(float fCurrent)
{
	MainUIObject->SetMonsterHP(fCurrent);
}

void APlayerUI_HUD::SetMonsterName(FString strMonsterName)
{
	MainUIObject->SetMonsterName(strMonsterName);
}
