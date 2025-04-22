// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Heroes/GDHeroCharacter.h"
#include "GDArenaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASDOCUMENTATION_API AGDArenaCharacter : public AGDHeroCharacter
{
	GENERATED_BODY()
	

public:
    // Constructor
    AGDArenaCharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ball")
    FName BallSocketName;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ball")
    class AScoreBall* HeldBall;

    void SetHeldBall(AScoreBall* NewBall);
    AScoreBall* GetHeldBall() const;
};
