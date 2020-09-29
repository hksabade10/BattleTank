// Fill out your copyright notice in the Description page of Project Settings.

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


public:

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons(N)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 40000.f;
	
};
