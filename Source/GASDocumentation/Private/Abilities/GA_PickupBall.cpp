#include "GA_PickupBall.h"
#include "GDHeroCharacter.h"
#include "ScoreBall.h"
#include "AbilitySystemComponent.h"

UGA_PickupBall::UGA_PickupBall()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_PickupBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    AGDHeroCharacter* Hero = Cast<AGDHeroCharacter>(ActorInfo->OwnerActor);
    if (!Hero) return;

    AScoreBall* Ball = /* Logic to find nearby ball */;
    if (!Ball) return;

    // Attach the ball
    Ball->AttachToCharacter(Hero, Hero->BallSocketName);
    Hero->SetHeldBall(Ball);

    // Add GameplayTag
    Hero->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.CarryingBall")));

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}