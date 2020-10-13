// Copyright hksabade10

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOffAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringState GetFiringState();

	// TODO Try AimAt as BlueprintCallable
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetCurrentRounds() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:

	void AimBarrelTowards(FVector Direction);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3.f;

	double LastFireTime = 0.f;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 TotalRounds = 5;

	int32 CurrentRounds = TotalRounds;

};


