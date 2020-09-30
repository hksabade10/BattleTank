// Copyright hksabade10

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Barrel is used to fire Projectile towards aim direction
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 to +1
	void ElevateBarrel(float RelativeElevation);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0.f;
	
};
