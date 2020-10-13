// Copyright hksabade10

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to apply driving force to Tank through Tracks
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	void ApplyLateralForce();

	float CurrentThrottle = 0.f;


public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons(N)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 20000000.f;


	
};
