// Copyright hksabade10


#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector HitLocation)
{
	if(!ensure(TankAimingComponent)) { return; }
	
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	
	bool bReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;

	if(!ensure(Barrel)) { return; }
	
	if(bReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing!"));

		auto CurrentProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		CurrentProjectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
		
}

