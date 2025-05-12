// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameMode.h"
#include "CombatComponent.generated.h"

class AUnitBase;
class AJRPGGameModeBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASDOCUMENTATION_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UCombatComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Combat|Turn Management")
    bool RequestTurn();

    UFUNCTION(BlueprintCallable, Category = "Combat|Turn Management")
    void StartTurn();

    UFUNCTION(BlueprintCallable, Category = "Combat|Turn Management")
    void EndTurn();

	UFUNCTION(BlueprintCallable, Category = "Combat|Turn Management")
	void BeginBattle();

	
	// Event Begin Battle, that will start this units battle timer. This will be overridden in blueprints
	UFUNCTION(BlueprintNativeEvent, Category = "Combat|Turn Management")
	void EventBeginBattle();

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsMyTurn;

    // Timer handle for turn requests
	UPROPERTY(BlueprintReadOnly, Category = "Combat|Turn Management")
    FTimerHandle TurnRequestTimer;

protected:
    UFUNCTION(BlueprintCallable, Category = "Combat|Turn Management")
    void HandleTurnRequest();

    UPROPERTY()
    AUnitBase* OwningUnit;
};
