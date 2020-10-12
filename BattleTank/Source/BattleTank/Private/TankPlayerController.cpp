// Copyright hksabade10


#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent)) { return; }
	
	SetTankAimingReference(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}


// Ticking
void ATankPlayerController::AimTowardsCrosshair()
{
	if(!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}


// Ticking
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrossairYLocation);

	FVector LookDirection;
	GetLookDirection(ScreenLocation, LookDirection);

	return GetLookVectorHitLocation(HitLocation, LookDirection);
	
}


// Ticking
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector LookLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, LookLocation, LookDirection);
}


// Ticking
bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceLength;

	FHitResult HitResult;
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	if(bIsHit)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);

	return false;
}




