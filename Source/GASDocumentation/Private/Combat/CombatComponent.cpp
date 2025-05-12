// Copyright 2023 Dan Kestranek.

#include "Combat/CombatComponent.h"
#include "Unit/UnitBase.h"
#include "JRPGGameModeBase.h"
// Add Timer Manager include
#include "Engine/World.h"
#include "TimerManager.h"


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
    //Call EventBeginBattle
    EventBeginBattle();
}

void UCombatComponent::EventBeginBattle_Implementation()
{
    if (!OwningUnit) return;

    // Log battle start
    UE_LOG(LogTemp, Warning, TEXT("Event Begin Battle for unit: %s"), *OwningUnit->GetName());

    // Create a Timer to call RequestTurn after 5 seconds
    GetWorld()->GetTimerManager().SetTimer<UCombatComponent>(
        TurnRequestTimer,        // Handle to the timer
        this,                    // Object context
        &UCombatComponent::HandleTurnRequest,  // Function to call
        5.0f,                   // Delay in seconds
        false                   // Loop?
    );

}

void UCombatComponent::HandleTurnRequest()
{
    // Call the RequestTurn function
    UE_LOG(LogTemp, Warning, TEXT("Handling Turn Request for Unit: %s"), *OwningUnit->GetName());
    RequestTurn();

}