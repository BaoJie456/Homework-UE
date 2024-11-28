// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetCubeJudge.h"


// Sets default values for this component's properties
UTargetCubeJudge::UTargetCubeJudge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	hitted = false;
	important = FMath::FRand() < 0.5f;
	// ...
}


// Called when the game starts
void UTargetCubeJudge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTargetCubeJudge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTargetCubeJudge::Attacked() {
	UE_LOG(LogTemp, Log, TEXT("Attacked"));
	AActor* owner = GetOwner();
	if (hitted) {
		owner->Destroy();
	} else {
		hitted = true;
		UStaticMeshComponent* mesh = owner->GetComponentByClass<UStaticMeshComponent>();
		mesh->SetRelativeScale3D(mesh->GetRelativeScale3D() * 0.5f);
	}
}

