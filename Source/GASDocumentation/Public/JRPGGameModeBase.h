// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Mode|Turn Management")
	void RequestTurn(AUnitBase* Unit);

	// Turn start - annotate these to be implemented in blueprints
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Mode|Turn Management")
	void StartTurn(AUnitBase* Unit);

	// Custom Properties - 
	UPROPERTY(BlueprintReadOnly, Category = "Game Mode|Turn Management")
	TArray<AUnitBase*> TurnOrder;

	// The delegate that will be exposed to Blueprint
    UPROPERTY(BlueprintAssignable, Category = "Turn System")
    FOnTurnRequestedDelegate OnTurnRequested;
	
};
