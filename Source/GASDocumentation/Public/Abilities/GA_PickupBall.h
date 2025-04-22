#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_PickupBall.generated.h"

UCLASS()
class GASDOCUMENTATION_API UGA_PickupBall : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGA_PickupBall();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};