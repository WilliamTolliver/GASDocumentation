// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBall.generated.h"

UCLASS()
class GASDOCUMENTATION_API AScoreBall : public AActor
{
    GENERATED_BODY()

public:
    AScoreBall();

    void BeginPlay();
    void Tick(float DeltaTime) override;
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    bool bIsHeld;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    class AGDArenaCharacter* BallCarrier;

    void AttachToCharacter(AGDArenaCharacter* Character, FName SocketName);
    void DetachFromCharacter();
};
