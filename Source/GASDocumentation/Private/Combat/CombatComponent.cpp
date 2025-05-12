// Copyright 2023 Dan Kestranek.

#include "Combat/CombatComponent.h"
#include "Unit/UnitBase.h"
#include "JRPGGameModeBase.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    bIsMyTurn = false;
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();
    OwningUnit = Cast<AUnitBase>(GetOwner());
}

bool UCombatComponent::RequestTurn()
{
    if (!OwningUnit) return false;

    if (AJRPGGameModeBase* GameMode = Cast<AJRPGGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->RequestTurn(OwningUnit);
        return true;
    }
    return false;
}

void UCombatComponent::StartTurn()
{
    bIsMyTurn = true;
    UE_LOG(LogTemp, Warning, TEXT("Turn started for unit: %s"), *OwningUnit->GetName());
}

void UCombatComponent::EndTurn()
{
    bIsMyTurn = false;
    UE_LOG(LogTemp, Warning, TEXT("Turn ended for unit: %s"), *OwningUnit->GetName());
}

void UCombatComponent::BeginBattle()
{
    // Implement battle start logic
    UE_LOG(LogTemp, Warning, TEXT("Battle started for unit: %s"), *OwningUnit->GetName());
}

