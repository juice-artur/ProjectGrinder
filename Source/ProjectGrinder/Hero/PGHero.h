// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "PGHero.generated.h"

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

/**
 *
 */
UCLASS()
class PROJECTGRINDER_API APGHero : public APaperZDCharacter
{
    GENERATED_BODY()
public:
    APGHero();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
    TObjectPtr<UInputAction> MoveForwardInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
    TObjectPtr<UInputAction> JumpInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "HeroInput")
    TObjectPtr<UInputMappingContext> InputMapping;

    void OnMoveForward(const FInputActionValue& Value);
    void OnJump(const FInputActionValue& Value);
    void OnJumpReleased(const FInputActionValue& Value);
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    virtual void Landed(const FHitResult& Hit) override;

    virtual void OnJumped_Implementation() override;
    virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal,
        const FVector& PreviousLocation, float TimeDelta) override;
};
