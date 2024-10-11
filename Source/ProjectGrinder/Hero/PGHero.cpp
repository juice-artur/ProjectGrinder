// Fill out your copyright notice in the Description page of Project Settings.


#include "PGHero.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void APGHero::OnMoveForward(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void APGHero::OnJump(const FInputActionValue& Value)
{
}

void APGHero::OnDush(const FInputActionValue& Value)
{
}

void APGHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(Input);
	Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &APGHero::OnMoveForward);
}

void APGHero::BeginPlay()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			constexpr int32 Priority = 0;
			Subsystem->AddMappingContext(InputMapping, Priority);
		}
	}

	Super::BeginPlay();
}


