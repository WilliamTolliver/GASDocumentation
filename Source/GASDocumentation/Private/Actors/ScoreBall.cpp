// Copyright 2023 Dan Kestranek.

#include "Actors/ScoreBall.h"
#include "Characters/Heroes/GDArenaCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AScoreBall::AScoreBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bIsHeld = false;
    BallCarrier = nullptr;
}

// Called when the game starts or when spawned
void AScoreBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreBall::AttachToCharacter(AGDArenaCharacter* Character, FName SocketName)
{
    if (!Character) return;

    BallCarrier = Character;
    bIsHeld = true;

    // Attach to the character's socket
    AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

    // Disable physics and collisions
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

void AScoreBall::DetachFromCharacter()
{
    BallCarrier = nullptr;
    bIsHeld = false;

    // Detach from the character
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    // Re-enable physics and collisions
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
}

