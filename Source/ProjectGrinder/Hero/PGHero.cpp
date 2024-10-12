// Fill out your copyright notice in the Description page of Project Settings.


#include "PGHero.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APGHero::APGHero()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

void APGHero::OnMoveForward(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	float Movement = Value.Get<float>();
	AddMovementInput(FVector(1, 0,0), Movement);
}

void APGHero::OnJump(const FInputActionValue& Value)
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


