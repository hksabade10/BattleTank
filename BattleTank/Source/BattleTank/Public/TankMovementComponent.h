// Copyright hksabade10

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;
class UTankTrack;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


protected:

	ATank* Tank = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TurnRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	

private:

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UTankTrack* Track_L = nullptr;
	
	UTankTrack* Track_R = nullptr;
	
};
