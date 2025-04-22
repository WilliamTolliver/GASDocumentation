#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_DropBall.generated.h"

UCLASS()
class GASDOCUMENTATION_API UGA_DropBall : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGA_DropBall();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};