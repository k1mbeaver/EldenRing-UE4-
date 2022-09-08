// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIMain_UW.h"
#include "PlayerUI_UW.h"

void UPlayerUIMain_UW::SetPlayerHP(float fCurrent)
{
	PlayerUI_WB->SetPlayerHP(fCurrent);
}

void UPlayerUIMain_UW::SetPlayerMP(float fCurrent)
{
	PlayerUI_WB->SetPlayerMP(fCurrent);
}

void UPlayerUIMain_UW::SetPlayerStamina(float fCurrent)
{
	PlayerUI_WB->SetPlayerStamina(fCurrent);
}

void UPlayerUIMain_UW::SetMonsterHP(float fCurrent)
{
	PlayerUI_WB->SetMonsterHP(fCurrent);
}

void UPlayerUIMain_UW::SetMonsterName(FString strMonsterName)
{
	PlayerUI_WB->SetMonsterName(strMonsterName);
}

void UPlayerUIMain_UW::SetMonsterVisible()
{
	PlayerUI_WB->SetMonsterVisible();
}