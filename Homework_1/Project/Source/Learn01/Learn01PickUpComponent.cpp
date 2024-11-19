// Copyright Epic Games, Inc. All Rights Reserved.

#include "Learn01PickUpComponent.h"

ULearn01PickUpComponent::ULearn01PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void ULearn01PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &ULearn01PickUpComponent::OnSphereBeginOverlap);
}

void ULearn01PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ALearn01Character* Character = Cast<ALearn01Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
