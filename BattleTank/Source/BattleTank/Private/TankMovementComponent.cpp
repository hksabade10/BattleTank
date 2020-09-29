// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Forward by : %f"), Value);
	
}
