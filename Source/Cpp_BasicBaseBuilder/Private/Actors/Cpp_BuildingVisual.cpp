// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_BuildingVisual.h"
#include "Components/StaticMeshComponent.h"

ACpp_BuildingVisual::ACpp_BuildingVisual() {
	PrimaryActorTick.bCanEverTick = false;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	
}

void ACpp_BuildingVisual::BeginPlay() {
	Super::BeginPlay();
	
	SetActorHiddenInGame(true);
}

void ACpp_BuildingVisual::SetBuildPosition(const FHitResult HitResult) {
	if (HitResult.bBlockingHit) {
		SetActorHiddenInGame(false);
		SetActorLocation(HitResult.Location);
	}
	else {
		SetActorHiddenInGame(true);
	}
}

