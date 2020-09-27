
// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possessed by PlayerController!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank : %s"), *(ControlledTank->GetName()));
	}	
}

ATank* ATankPlayerController::GetControlledTank() const
{	
	return Cast<ATank>(GetPawn());;
}
