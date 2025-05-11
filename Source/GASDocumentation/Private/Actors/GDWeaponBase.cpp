// Copyright 2023 Dan Kestranek.


#include "Actors/GDWeaponBase.h"

// Sets default values
AGDWeaponBase::AGDWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGDWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

