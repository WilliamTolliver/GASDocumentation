#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BattlePositionData.generated.h"

UCLASS(BlueprintType)
class GASDOCUMENTATION_API UBattlePositionData : public UDataAsset
{
    GENERATED_BODY()

public:
    // Array of transform for player party positions
    UPROPERTY(EditDefaultsOnly, Category = "Battle|Positions")
    TArray<FTransform> PlayerPartyPositions;

    // Array of transform for enemy party positions
    UPROPERTY(EditDefaultsOnly, Category = "Battle|Positions")
    TArray<FTransform> EnemyPartyPositions;
};