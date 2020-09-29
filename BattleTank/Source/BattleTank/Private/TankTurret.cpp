// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"


void UTankTurret::RotateTurret(float RelativeYawRotation)
{
	RelativeYawRotation = FMath::Clamp<float>(RelativeYawRotation, -1, 1);
	float DeltaRotation = RelativeYawRotation * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = GetRelativeRotation().Yaw + DeltaRotation;

	
	
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
