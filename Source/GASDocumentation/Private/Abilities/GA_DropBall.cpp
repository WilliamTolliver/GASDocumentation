#include "GA_DropBall.h"
#include "GDHeroCharacter.h"
#include "ScoreBall.h"
#include "AbilitySystemComponent.h"

UGA_DropBall::UGA_DropBall()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_DropBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    AGDHeroCharacter* Hero = Cast<AGDHeroCharacter>(ActorInfo->OwnerActor);
    if (!Hero) return;

    AScoreBall* Ball = Hero->GetHeldBall();
    if (!Ball) return;

    // Detach the ball
    Ball->DetachFromCharacter();
    Hero->SetHeldBall(nullptr);

    // Remove GameplayTag
    Hero->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.CarryingBall")));

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}