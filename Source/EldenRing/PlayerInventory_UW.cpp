// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory_UW.h"

void UPlayerInventory_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//MonsterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MonsterName")));
}

void UPlayerInventory_UW::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventory_UW::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}