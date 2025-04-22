#include "ScoreBall.h"
#include "GDHeroCharacter.h"
#include "Components/SkeletalMeshComponent.h"

AScoreBall::AScoreBall()
{
    bIsHeld = false;
    BallCarrier = nullptr;
}

void AScoreBall::AttachToCharacter(AGDHeroCharacter* Character, FName SocketName)
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