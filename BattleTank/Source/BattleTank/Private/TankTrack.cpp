// Copyright hksabade10


#include "TankTrack.h"


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplyLateralForce()
{
	// Finding lateral accelearation
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());
	FVector Deceleration = - SlippageSpeed / DeltaTime * GetRightVector();

	// Applying force in opposite direction
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * Deceleration) / 2;			// Two Tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplyLateralForce();
	CurrentThrottle = 0.f;
}

void UTankTrack::DriveTrack()
{
	FVector AppliedForce = GetForwardVector() * MaxDrivingForce * CurrentThrottle;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
