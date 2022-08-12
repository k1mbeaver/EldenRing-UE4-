// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn)
	{
		myCharacter = Cast<APlayerCharacter>(aPawn);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
		SetInputMode(FInputModeGameOnly());
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);

	// 캐릭터 이동 함수
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AMyPlayerController::Turn);

	// 캐릭터 점프 함수
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJumping);

	// 캐릭터 공격 함수
	InputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayerController::Attack);

	// 캐릭터 달리기 함수
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayerController::StopRun);


	// 캐릭터 스킬 함수
	InputComponent->BindAction("Skill", IE_Pressed, this, &AMyPlayerController::Skill);
	InputComponent->BindAction("Skill", IE_Released, this, &AMyPlayerController::StopSkillIntro);

	// 플레이어 일시정지 함수
	//InputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerController::PlayerPause);
}


void AMyPlayerController::UpDown(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->UpDown(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("UpDown!"));
	}
}

void AMyPlayerController::LeftRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LeftRight(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftRight!"));
	}
}

void AMyPlayerController::LookUp(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LookUp(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LookUp!"));
	}
}

void AMyPlayerController::Turn(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->Turn(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Turn!"));
	}
}


void AMyPlayerController::Jump()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Jump();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::Skill()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Skill();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::StopSkillIntro()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopSkillIntro();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::StopJumping()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopJumping();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopJumping!"));
	}
}

void AMyPlayerController::Attack()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Attack();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack!"));
	}
}

void AMyPlayerController::Run()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Run();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Run!"));
	}
}

void AMyPlayerController::StopRun()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopRun();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

/*
void AMyPlayerController::PlayerPause()
{
	if (myCharacter != nullptr)
	{
		myCharacter->PlayerPause();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPause!"));
	}
}
*/