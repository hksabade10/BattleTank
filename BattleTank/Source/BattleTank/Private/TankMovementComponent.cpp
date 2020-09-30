// Copyright hksabade10


#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	Track_L = LeftTrack;
	Track_R = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardDirection = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("%s is vectoring to %s"), *(GetOwner()->GetName()), *MoveVelocityString);

	float DotProduct = FVector::DotProduct(TankForwardDirection, AIForwardDirection);

	FVector CrossProduct = FVector::CrossProduct(TankForwardDirection, AIForwardDirection);

	MoveForward(DotProduct);
	TurnRight(CrossProduct.Z);
}

void UTankMovementComponent::MoveForward(float Value)
{
	if(!Track_L || !Track_R) { return; }
	Track_L->SetThrottle(Value);
	Track_R->SetThrottle(Value);
}

void UTankMovementComponent::TurnRight(float Value)
{
	if(!Track_L || !Track_R) { return; }
	Track_R->SetThrottle(-Value);
	Track_L->SetThrottle(Value);
}



