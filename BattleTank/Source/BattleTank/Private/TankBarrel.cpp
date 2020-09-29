// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeElevation)
{
	RelativeElevation = FMath::Clamp<float>(RelativeElevation, -1, 1);
	float DeltaElevation = RelativeElevation * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = GetRelativeRotation().Pitch + DeltaElevation;
	NewElevation = FMath::ClampAngle(NewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
	
}
