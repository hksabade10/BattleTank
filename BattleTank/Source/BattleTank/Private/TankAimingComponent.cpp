// Copyright hksabade10


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


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

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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

		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f : Have Aim Solution"), Time);
	}
	else
	{
		// auto Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f : No Aim Solution"), Time);
	}
}

void UTankAimingComponent::AimBarrelTowards(FVector AimDirection)
{
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = Barrel->GetForwardVector().Rotation().Yaw - AimDirection.Rotation().Yaw;

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	// auto TankController = Cast<ATankPlayerController>(GetOwner()->GetInstigatorController());
	// if(!TankController) { return; }
	// auto Input = TankController->GetInputAxisValue("AimAzimuth");
	

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);

	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotation : %s"), *DeltaRotation.ToString());
	
}





