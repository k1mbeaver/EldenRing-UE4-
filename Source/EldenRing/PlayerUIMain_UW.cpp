// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIMain_UW.h"
#include "PlayerUI_UW.h"
#include "PlayerInventory_UW.h"
#include "ItemStruct.h"

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

void UPlayerUIMain_UW::SetPotionAmount(FString strPotionType, int nAmount)
{
	PlayerUI_WB->SetPotionAmount(strPotionType, nAmount);
}

void UPlayerUIMain_UW::SetVisible()
{
	PlayerInventory_WB->SetVisible();
}

void UPlayerUIMain_UW::SetHidden()
{
	PlayerInventory_WB->SetHidden();
}

void UPlayerUIMain_UW::SetItemDescriptHidden()
{
	PlayerInventory_WB->SetItemDescriptHidden();
}

void UPlayerUIMain_UW::SetItemDescriptVisible()
{
	PlayerInventory_WB->SetItemDescriptVisible();
}

void UPlayerUIMain_UW::SetItemDescript(FString setItemName, FString setItemDescript, UTexture2D* setItemImage)
{
	PlayerInventory_WB->SetItemDescript(setItemName, setItemDescript, setItemImage);
}

void UPlayerUIMain_UW::SetSlot(int nSlot, TArray<FPlayerItem> arrInventory)
{
	PlayerInventory_WB->SetSlot(nSlot, arrInventory);
}