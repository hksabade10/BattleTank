// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


protected:

	ATank* Tank = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Value);
	
};
