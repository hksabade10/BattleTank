// Copyright hksabade10


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector AppliedForce = GetForwardVector() * MaxDrivingForce * Throttle;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}
