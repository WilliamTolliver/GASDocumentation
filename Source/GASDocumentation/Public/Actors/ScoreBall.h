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

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    bool bIsHeld;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    class AGDHeroCharacter* BallCarrier;

    void AttachToCharacter(AGDHeroCharacter* Character, FName SocketName);
    void DetachFromCharacter();
};