// Copyright 2023 Dan Kestranek.


#include "Characters/Heroes/GDArenaCharacter.h"
#include "Actors/ScoreBall.h"

// Constructor
AGDArenaCharacter::AGDArenaCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) // Call the parent class constructor
{
    // Initialize default values
    BallSocketName = "BallSocket";
    HeldBall = nullptr;
}

// Sets the currently held ball
void AGDArenaCharacter::SetHeldBall(AScoreBall* NewBall)
{
    HeldBall = NewBall;
}

// Gets the currently held ball
AScoreBall* AGDArenaCharacter::GetHeldBall() const
{
    return HeldBall;
}