// Copyright hksabade10


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{	
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel && Turret)) { return; }

	FVector LaunchVelocity;
	FVector BarrelLocation = Barrel->GetSocketLocation("Projectile");
	
	
	bool bHaveAimSolution = 
	UGameplayStatics::SuggestProjectileVelocity
	(
		this, 
		LaunchVelocity, 
		BarrelLocation, 
		HitLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if(bHaveAimSolution)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		AimBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::AimBarrelTowards(FVector AimDirection)
{
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = Barrel->GetForwardVector().Rotation().Yaw - AimDirection.Rotation().Yaw;

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if(!ensure(Barrel && Projectile)) { return; }
	bool bReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;

	if(bReloaded)
	{
		auto CurrentProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		CurrentProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}