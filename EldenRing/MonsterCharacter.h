// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class ELDENRING_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

	//UPROPERTY(VisibleInstanceOnly, Category = Animation)
		//class UAIAnimInstance* AIAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = true))
		float MonsterSpeed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		float fAIHp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		float fMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* DeathSound;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		//class UWidgetComponent* AIWidget;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		//class UStaticMeshComponent* HPStatic;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = HP, Meta = (AllowPrivateAccess = true))
		//class UAIHPBar_UW* MonsterHpBar;

	//UPROPERTY(EditDefaultsOnly, Category = HP)
	//	TSubclassOf<class UUserWidget> MONSTER_HPClass;

	//UPROPERTY(EditDefaultsOnly, Category = HP)
		//TSubclassOf<class UAIHPBar_UW> MONSTER_HPTClass;

	// damage particle
	UPROPERTY()
		class UParticleSystem* DamageParticle;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	// TakeDamage의 경우에도 다시 해보자
	//float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();
	//void AttackCheck();
	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	//void AttackByPlayer(float DamageAmount);
	void StopAIController();
	void InitializeAI(FString MonsterType);
};
