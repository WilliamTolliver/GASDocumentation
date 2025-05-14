// Copyright 2023 Dan Kestranek.

#include "JRPGGameModeBase.h"
#include "Unit/UnitBase.h"
#include "Kismet/GameplayStatics.h"


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
    // Load positions if not already loaded
    if (BattlePositionData)
    {
        LoadBattlePositions(BattlePositionData);
        AssignBattlePositions();
    }

    // Default C++ implementation - can be empty if you want all logic in Blueprint
    // This will run if no Blueprint override is provided
    GetAllCombatants();

    UE_LOG(LogTemp, Warning, TEXT("Battle started!"));
    // Start the battle logic here

    // Tell all units with a CombatComponent to begin battle
    for (AUnitBase* Unit : Combatants)
    {
        if (Unit && Unit->CombatComponent)
        {
            Unit->CombatComponent->BeginBattle();
        }
    }
}

// This function is called to get all combatants in the game
void AJRPGGameModeBase::GetAllCombatants()
{
    // This function should be implemented to populate the Combatants array
    // For example, you might want to find all units in the level and add them to the array
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitBase::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        AUnitBase* Unit = Cast<AUnitBase>(Actor);
        if (Unit)
        {
            Combatants.Add(Unit);
        }
    }
}

void AJRPGGameModeBase::LoadBattlePositions(UBattlePositionData* NewBattleData)
{
    if (!NewBattleData) return;

    BattlePositionData = NewBattleData;
    CurrentPlayerPositions = BattlePositionData->PlayerPartyPositions;
    CurrentEnemyPositions = BattlePositionData->EnemyPartyPositions;
}

void AJRPGGameModeBase::AssignBattlePositions()
{
    // Assign player party positions
    for (int32 i = 0; i < PlayerParty.Num() && i < CurrentPlayerPositions.Num(); ++i)
    {
        if (PlayerParty[i])
        {
            PlayerParty[i]->SetActorTransform(CurrentPlayerPositions[i]);
        }
    }

    // Assign enemy party positions
    for (int32 i = 0; i < EnemyParty.Num() && i < CurrentEnemyPositions.Num(); ++i)
    {
        if (EnemyParty[i])
        {
            EnemyParty[i]->SetActorTransform(CurrentEnemyPositions[i]);
        }
    }
}