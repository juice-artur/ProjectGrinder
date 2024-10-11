// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "PGHero.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECTGRINDER_API APGHero : public APaperZDCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
	TObjectPtr<UInputAction> MoveForwardInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
	TObjectPtr<UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
	TObjectPtr<UInputAction> DushInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
	TObjectPtr<UInputMappingContext> InputMapping;

	void OnMoveForward(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnDush(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void BeginPlay() override;
	
};
