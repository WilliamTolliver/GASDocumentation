// ScoreBall.cpp
#include "Actors/ScoreBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/Heroes/GDArenaCharacter.h"
#include "Actors/GoalArea.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

AScoreBall::AScoreBall()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->SetSphereRadius(140.0f);
    
    // Change collision settings to allow overlaps
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    
    CollisionComponent->SetNotifyRigidBodyCollision(true); // For hit events
    CollisionComponent->SetGenerateOverlapEvents(true);    // Enable overlap events
    CollisionComponent->SetSimulatePhysics(false);
   
    CollisionComponent->OnComponentHit.AddDynamic(this, &AScoreBall::OnBallHit);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AScoreBall::OnBallOverlap);
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1000.0f;
    ProjectileMovement->MaxSpeed = 1000.0f;
    ProjectileMovement->bShouldBounce = true;

    bIsHeld = false;
    BallCarrier = nullptr;
}

void AScoreBall::BeginPlay()
{
    Super::BeginPlay();
}

void AScoreBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AScoreBall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    UE_LOG(LogTemp, Warning, TEXT("Ball Hit: %s"), *OtherActor->GetName());
    if (bIsHeld || !OtherActor || OtherActor == this) return;

    if (AGDArenaCharacter* Character = Cast<AGDArenaCharacter>(OtherActor))
    {
        HandleCatch(Character);
    }
    else if (OtherActor->IsA(AGoalArea::StaticClass()))
    {
        HandleScore(OtherActor);
    }
}

void AScoreBall::OnBallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    UE_LOG(LogTemp, Warning, TEXT("Ball Overlapping: %s"), *OtherActor->GetName());
    if (bIsHeld || !OtherActor || OtherActor == this) return;

    if (AGDArenaCharacter* Character = Cast<AGDArenaCharacter>(OtherActor))
    {
    HandleCatch(Character);
    }
    else if (OtherActor->IsA(AGoalArea::StaticClass()))
    {
    HandleScore(OtherActor);
    }
}

void AScoreBall::HandleCatch(AGDArenaCharacter* Catcher)
{
    if (!Catcher) return;

    BallCarrier = Catcher;
    bIsHeld = true;

    ProjectileMovement->StopMovementImmediately();
    SetActorEnableCollision(false);

    // Apply gameplay tag or notify GAS system (to be implemented)
    // Example: Catcher->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.CarryingBall"));
}

void AScoreBall::HandleScore(AActor* Goal)
{
    if (BallCarrier)
    {
        // Notify GameMode or ScoringSystem
        if (AGameModeBase* GM = UGameplayStatics::GetGameMode(this))
        {
            // Cast to custom GameMode and call scoring logic
            // Example: Cast<ACustomGameMode>(GM)->ScoreGoal(BallCarrier);
        }
    }

    // Reset state
    BallCarrier = nullptr;
    bIsHeld = false;
    SetActorEnableCollision(true);
    ProjectileMovement->StopMovementImmediately();
    // Optionally destroy or respawn ball
}
