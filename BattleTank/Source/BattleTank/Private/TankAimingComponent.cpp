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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	if(CurrentRounds <= 0)
	{
		FiringState = EFiringState::OutOffAmmo;
	}
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

	
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringState;
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
		AimDirection = LaunchVelocity.GetSafeNormal();
		AimBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::AimBarrelTowards(FVector Direction)
{
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = Barrel->GetForwardVector().Rotation().Yaw - AimDirection.Rotation().Yaw;

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = Direction.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}	
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
		
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)) { return false; }
	auto ForwardVector = Barrel->GetForwardVector();
	return !(ForwardVector.Equals(AimDirection, 0.01));
}


int32 UTankAimingComponent::GetCurrentRounds() const
{
	return CurrentRounds;
}

void UTankAimingComponent::Fire()
{
	if(!ensure(Barrel)) { return; }
	if(!ensure(Projectile)) { return; }
	
	if(FiringState == EFiringState::Aiming && FiringState == EFiringState::Locked)
	{
		auto CurrentProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		CurrentProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		CurrentRounds--;
	}
}