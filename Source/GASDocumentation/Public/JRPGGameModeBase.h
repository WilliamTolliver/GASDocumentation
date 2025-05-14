// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/BattlePositionData.h"
#include "JRPGGameModeBase.generated.h"

/**
 * 
 */
// Define 2 delegates for turn management
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnRequestedDelegate, AUnitBase*, Unit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnStartDelegate, AUnitBase*, Unit);

UCLASS()
class GASDOCUMENTATION_API AJRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJRPGGameModeBase();

	// Custom Events
	// Turn request - annotate these to be implemented in blueprints
	UFUNCTION(BlueprintCallable, Category = "Game Mode|Turn Management")
	void RequestTurn(AUnitBase* Unit);

	// Turn start - annotate these to be implemented in blueprints
	UFUNCTION(BlueprintCallable, Category = "Game Mode|Turn Management")
	void StartTurn(AUnitBase* Unit);

	UFUNCTION(BlueprintCallable, Category = "Game Mode|Turn Management")
	void EndTurn(AUnitBase* Unit);

	UFUNCTION(BlueprintCallable, Category = "Game Mode|Turn Management")
	void BeginBattle();

	UFUNCTION(BlueprintCallable, Category = "Game Mode|Turn Management")
	void GetAllCombatants();

	// Custom Properties - 
	UPROPERTY(BlueprintReadOnly, Category = "Game Mode|Turn Management")
	TArray<AUnitBase*> TurnOrder;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode|Turn Management")
	TArray<AUnitBase*> Combatants;

	// The delegate that will be exposed to Blueprint
    UPROPERTY(BlueprintAssignable, Category = "Turn System")
    FOnTurnRequestedDelegate OnTurnRequested;

    // Battle position data asset
    UPROPERTY(EditDefaultsOnly, Category = "Battle|Setup")
    UBattlePositionData* BattlePositionData;

    // Arrays to track parties
    UPROPERTY(BlueprintReadOnly, Category = "Battle|Parties")
    TArray<AUnitBase*> PlayerParty;

    UPROPERTY(BlueprintReadOnly, Category = "Battle|Parties")
    TArray<AUnitBase*> EnemyParty;

    // Arrays to store current battle positions
    UPROPERTY(BlueprintReadOnly, Category = "Battle|Positions")
    TArray<FTransform> CurrentPlayerPositions;

    UPROPERTY(BlueprintReadOnly, Category = "Battle|Positions")
    TArray<FTransform> CurrentEnemyPositions;

    // Function to load and setup battle positions
    UFUNCTION(BlueprintCallable, Category = "Battle|Setup")
    void LoadBattlePositions(UBattlePositionData* NewBattleData);

    // Arrays to store unit classes to spawn
    UPROPERTY(EditDefaultsOnly, Category = "Battle|Setup")
    TArray<TSubclassOf<AUnitBase>> PlayerPartyClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Battle|Setup")
    TArray<TSubclassOf<AUnitBase>> EnemyPartyClasses;

    // Function to spawn combatants
    UFUNCTION(BlueprintCallable, Category = "Battle|Setup")
    void SpawnCombatants();

protected:
    // Function to assign positions to units
    virtual void AssignBattlePositions();

    // Helper functions for spawning
    void SpawnPlayerParty();
    void SpawnEnemyParty();
};
