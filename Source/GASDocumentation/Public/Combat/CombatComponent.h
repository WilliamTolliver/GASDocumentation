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

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsMyTurn;
	
protected:

    UPROPERTY()
    AUnitBase* OwningUnit;
};
