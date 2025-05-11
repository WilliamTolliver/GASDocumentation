// Copyright 2023 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Characters/Abilities/GDAbilitySystemComponent.h"
#include "Characters/Abilities/AttributeSets/GDAttributeSetBase.h"
#include "UnitBase.generated.h"

UCLASS()
class GASDOCUMENTATION_API AUnitBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AUnitBase();

    // Implement IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    // Turn Management
    UFUNCTION(BlueprintCallable, Category = "Unit|Turn Management")
    virtual void StartTurn();

    UFUNCTION(BlueprintCallable, Category = "Unit|Turn Management")
    virtual void EndTurn();

    UFUNCTION(BlueprintCallable, Category = "Unit|Turn Management")
    virtual bool RequestTurn();

    // Getters for attributes
    UFUNCTION(BlueprintCallable, Category = "Unit|Attributes")
    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Unit|Attributes")
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Unit|Attributes")
    float GetMana() const;

    UFUNCTION(BlueprintCallable, Category = "Unit|Attributes")
    float GetMaxMana() const;

protected:
    virtual void BeginPlay() override;

    // Ability System Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UGDAbilitySystemComponent* AbilitySystemComponent;

    // Attribute Set
    UPROPERTY()
    UGDAttributeSetBase* AttributeSet;

    // Turn Management
    UPROPERTY(BlueprintReadOnly, Category = "Unit|Turn Management")
    bool bIsMyTurn;

    // Initialize abilities and attributes
    virtual void InitializeAttributes();
    virtual void GiveAbilities();

private:
    // Helper function to bind to attribute changes
    virtual void BindAttributeChangeDelegates();
    
public:    
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
