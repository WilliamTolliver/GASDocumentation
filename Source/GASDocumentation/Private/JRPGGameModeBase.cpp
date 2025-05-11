// Copyright 2023 Dan Kestranek.

#include "JRPGGameModeBase.h"
#include "Unit/UnitBase.h"

AJRPGGameModeBase::AJRPGGameModeBase()
{
    // Constructor implementation
}

// For BlueprintNativeEvent functions, we implement the _Implementation version
void AJRPGGameModeBase::RequestTurn_Implementation(AUnitBase* Unit)
{
    // Default C++ implementation - can be empty if you want all logic in Blueprint
    // This will run if no Blueprint override is provided

    UE_LOG(LogTemp, Warning, TEXT("Turn requested for unit: %s"), *Unit->GetName());
    // For example, you might want to add the unit to the turn order
    TurnOrder.Add(Unit);
    // Notify Blueprint that a turn has been requested
    OnTurnRequested.Broadcast(Unit);
}

void AJRPGGameModeBase::StartTurn_Implementation(AUnitBase* Unit)
{
    // Default C++ implementation - can be empty if you want all logic in Blueprint
    // This will run if no Blueprint override is provided

    UE_LOG(LogTemp, Warning, TEXT("Turn started for unit: %s"), *Unit->GetName());
    // Start Turn for next unit in the turn order
    if (TurnOrder.Num() > 0)
    {
        AUnitBase* NextUnit = TurnOrder[0];
        TurnOrder.RemoveAt(0); // Remove the unit from the turn order
        NextUnit->StartTurn(); // Call StartTurn on the next unit
    }
}




