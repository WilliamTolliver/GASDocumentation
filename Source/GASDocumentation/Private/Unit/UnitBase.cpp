// Copyright 2023 Dan Kestranek.

#include "Unit/UnitBase.h"
#include "JRPGGameModeBase.h"
#include "Characters/Abilities/GDAbilitySystemComponent.h"
#include "Characters/Abilities/AttributeSets/GDAttributeSetBase.h"
// include gamemodebase header
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameModeBase.h"



// Sets default values
AUnitBase::AUnitBase()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create Ability System Component
    AbilitySystemComponent = CreateDefaultSubobject<UGDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    // Create the Attribute Set
    AttributeSet = CreateDefaultSubobject<UGDAttributeSetBase>(TEXT("AttributeSet"));

    bIsMyTurn = false;
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        InitializeAttributes();
        GiveAbilities();
        BindAttributeChangeDelegates();
    }
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AUnitBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AUnitBase::InitializeAttributes()
{
    if (!AbilitySystemComponent)
        return;

    // Initialize attributes here using GameplayEffects
    // This would typically be done using data tables and gameplay effects
}

void AUnitBase::GiveAbilities()
{
    if (!AbilitySystemComponent)
        return;

    // Grant abilities here
    // This would be implemented based on your specific ability needs
}

void AUnitBase::BindAttributeChangeDelegates()
{
    if (!AbilitySystemComponent || !AttributeSet)
        return;

    // Bind to attribute changes here if needed
}

void AUnitBase::StartTurn()
{
    bIsMyTurn = true;
    // Implement turn start logic here
}

void AUnitBase::EndTurn()
{
    bIsMyTurn = false;
    // Implement turn end logic here
}

bool AUnitBase::RequestTurn()
{
    // Implement turn request logic here
	// Make the request to the GameMode
	if (GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("Requesting turn for unit: %s"), *GetName());
		AJRPGGameModeBase* GameMode = Cast<AJRPGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->RequestTurn(this);
			return true;
		}
	}
    return false;
}

float AUnitBase::GetHealth() const
{
    if (!AttributeSet)
        return 0.0f;

    return AttributeSet->GetHealth();
}

float AUnitBase::GetMaxHealth() const
{
    if (!AttributeSet)
        return 0.0f;

    return AttributeSet->GetMaxHealth();
}

float AUnitBase::GetMana() const
{
    if (!AttributeSet)
        return 0.0f;

    return AttributeSet->GetMana();
}

float AUnitBase::GetMaxMana() const
{
    if (!AttributeSet)
        return 0.0f;

    return AttributeSet->GetMaxMana();
}

