// Copyright hksabade10


#include "TankAIController.h"
#include "TankAimingComponent.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if(!ensure(PlayerTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire after locking the aim
	AimingComponent->Fire();
	
}




