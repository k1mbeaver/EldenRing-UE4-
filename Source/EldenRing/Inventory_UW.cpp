// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "PlayerItemData.h"

void UInventory_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescript = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescript")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemListView = Cast<UListView>(GetWidgetFromName(TEXT("ItemListView")));
}

void UInventory_UW::SetImage(UTexture2D* Image)
{
	ItemImage->SetBrushFromTexture(Image);
}

void UInventory_UW::SetName(FString strName)
{
	ItemName->SetText(FText::FromString(strName));
}

void UInventory_UW::SetDescript(FString strDescript)
{
	ItemDescript->SetText(FText::FromString(strDescript));
}

void UInventory_UW::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UPlayerItemData* ItemData = NewObject<UPlayerItemData>(this, UPlayerItemData::StaticClass());
	ItemData->SetItemIndex(nIndex);
	ItemData->SetItemCount(nCount);
	ItemData->SetItemName(strName);
	ItemData->SetItemImage(setImage);
	ItemListView->AddItem(ItemData);
}

void UInventory_UW::Init()
{
	ItemImage->SetBrushFromTexture(nullptr);
	ItemName->SetText(FText::FromString(""));
	ItemDescript->SetText(FText::FromString(""));
}
