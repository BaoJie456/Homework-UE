// Copyright Epic Games, Inc. All Rights Reserved.

#include "Learn01Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TargetCubeJudge.h"

ALearn01Projectile::ALearn01Projectile() 
{
	UE_LOG(LogTemp, Log, TEXT("Pro"));
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ALearn01Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ALearn01Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		UTargetCubeJudge* judge = OtherActor->GetComponentByClass<UTargetCubeJudge>();
		if (judge != nullptr) {
			judge->Attacked();
			Character->Score();
			if (judge->important) {
				Character->Score();
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("not target"));
		}
		
		/*UClass* type = OtherActor->GetClass();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *type->GetName());
		ATargetCube* cube = Cast<ATargetCube>(OtherActor);
		if (cube != nullptr) {
			cube->Attacked();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("not cube"));
		}*/


		//actor->Attacked();
		/*FVector scale = OtherActor->GetActorRelativeScale3D();
		if (scale.X > 0.5f) {
			OtherActor->SetActorRelativeScale3D(scale * 0.5f);
		} else {
			OtherActor->Destroy();
		}*/
		Destroy();
	}
}

