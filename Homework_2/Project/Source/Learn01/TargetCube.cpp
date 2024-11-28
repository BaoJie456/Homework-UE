// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetCube.h"


// Sets default values
ATargetCube::ATargetCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hitted = false;
}

// Called when the game starts or when spawned
void ATargetCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATargetCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATargetCube::Attacked() {
	UE_LOG(LogTemp, Log, TEXT("attack"));
	if (hitted) {
		Destroy();
	} else {
		hitted = true;
		SetActorRelativeScale3D(GetActorRelativeScale3D() * 0.5f);
	}
}
