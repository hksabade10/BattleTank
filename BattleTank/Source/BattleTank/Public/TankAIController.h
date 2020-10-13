// Copyright hksabade10

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	UTankAimingComponent* AimingComponent = nullptr;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5000.f;

};
