// Fill out your copyright notice in the Description page of Project Settings.

#include "PGHero.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"

APGHero::APGHero()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void APGHero::OnMoveForward(const FInputActionValue& Value)
{
    float Movement = Value.Get<float>();
    AddMovementInput(FVector(1, 0, 0), Movement);
}

void APGHero::OnJumpReleased(const FInputActionValue& Value)
{
    StopJumping();
}

void APGHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    check(Input);
    Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &APGHero::OnMoveForward);
    Input->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &APGHero::OnJump);
    Input->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &APGHero::OnJumpReleased);
}

void APGHero::BeginPlay()
{
    if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            constexpr int32 Priority = 0;
            Subsystem->AddMappingContext(InputMapping, Priority);
        }
    }

    Super::BeginPlay();
}

void APGHero::Tick(float DeltaSeconds)
{
    if (this->GetMovementComponent()->Velocity.X > 0)
    {
        GetController()->SetControlRotation(FRotator3d());
    }
    else if (this->GetMovementComponent()->Velocity.X < 0)
    {
        GetController()->SetControlRotation(FRotator3d(0, 180, 0));
    }
}

void APGHero::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    this->GetAnimationComponent()->GetAnimInstance()->JumpToNode("Landed");
}

void APGHero::OnJump(const FInputActionValue& Value)
{
    Jump();

    if (UPaperZDAnimationComponent* AnimationComp = this->GetAnimationComponent())
    {
        if (UPaperZDAnimInstance* AnimInst = AnimationComp->GetAnimInstance())
        {
            AnimInst->JumpToNode("JumpAction");
        }
    }
}
