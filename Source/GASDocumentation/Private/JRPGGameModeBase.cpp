// Copyright 2023 Dan Kestranek.

#include "JRPGGameModeBase.h"
#include "Unit/UnitBase.h"

AJRPGGameModeBase::AJRPGGameModeBase()
{
    // Constructor implementation
}

// For BlueprintNativeEvent functions, we implement the _Implementation version
void AJRPGGameModeBase::RequestTurn(AUnitBase* Unit)
{
    // Default C++ implementation - can be empty if you want all logic in Blueprint
    // This will run if no Blueprint override is provided

    UE_LOG(LogTemp, Warning, TEXT("Turn requested for unit: %s"), *Unit->GetName());
    // For example, you might want to add the unit to the turn order
    TurnOrder.Add(Unit);
    // Notify Blueprint that a turn has been requested
    OnTurnRequested.Broadcast(Unit);

    AJRPGGameModeBase::StartTurn(Unit);
}

void AJRPGGameModeBase::StartTurn(AUnitBase* Unit)
{
    if (!Unit) return;

    UE_LOG(LogTemp, Warning, TEXT("Attempting to grant turn for unit: %s"), *Unit->GetName());
    
    if (TurnOrder.Num() > 0)
    {
        AUnitBase* NextUnit = TurnOrder[0];
        if (NextUnit && NextUnit->CombatComponent)
        {
            NextUnit->CombatComponent->StartTurn();
        }
    }
}

void AJRPGGameModeBase::EndTurn(AUnitBase* Unit)
{
    if (!Unit || !Unit->CombatComponent) return;

    UE_LOG(LogTemp, Warning, TEXT("Turn ended for unit: %s"), *Unit->GetName());
    Unit->CombatComponent->EndTurn();
}

void AJRPGGameModeBase::BeginBattle()
{
    // Default C++ implementation - can be empty if you want all logic in Blueprint
    // This will run if no Blueprint override is provided

    UE_LOG(LogTemp, Warning, TEXT("Battle started!"));
    // Start the battle logic here
}
