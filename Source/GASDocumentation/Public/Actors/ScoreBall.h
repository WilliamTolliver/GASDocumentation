// ScoreBall.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBall.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AGDArenaCharacter;
class AGoalArea;

UCLASS()
class GASDOCUMENTATION_API AScoreBall : public AActor
{
    GENERATED_BODY()

public:
    AScoreBall();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    bool bIsHeld;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "ScoreBall")
    AGDArenaCharacter* BallCarrier;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ScoreBall")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ScoreBall")
    UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION()
    void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void OnBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    void HandleCatch(AGDArenaCharacter* Catcher);
    void HandleScore(AActor* Goal);
};
