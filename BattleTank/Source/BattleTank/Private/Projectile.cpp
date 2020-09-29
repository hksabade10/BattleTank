// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpawnTime = FPlatformTime::Seconds();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto CurrentTime = FPlatformTime::Seconds();

	if(CurrentTime - SpawnTime > 10.f)
	{
		Destroy(true);
	}

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	FVector LaunchVector = FVector::ForwardVector * LaunchSpeed;
	ProjectileMovement->SetVelocityInLocalSpace(LaunchVector);
	ProjectileMovement->Activate();
}

