// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventory_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UPlayerInventory_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//UPROPERTY(Meta = (BindWidget))
		//class UTextBlock* MonsterName;

protected:
	virtual void NativeOnInitialized() override;
	//virtual void NativeConstruct() override;
public:

	void SetVisible();
	void SetHidden();
};
