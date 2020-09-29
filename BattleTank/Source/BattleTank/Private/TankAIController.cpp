// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = Cast<ATank>(GetPawn());

	
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is not possessed by AIController!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank : %s"),*(ControlledTank->GetName()));
	}
	
	ATank* PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIContoller unable to find PlayerTank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank : %s"),*(PlayerTank->GetName()));
	}
	
}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(PlayerTank)
	{
		// Move towards the player

		// Aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire after locking the aim
		ControlledTank->Fire();			// TODO limmit firing rate
	}
}




