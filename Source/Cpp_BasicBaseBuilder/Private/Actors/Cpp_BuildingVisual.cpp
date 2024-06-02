// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_BuildingVisual.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Cpp_Building_Base.h"

ACpp_BuildingVisual::ACpp_BuildingVisual() {
	PrimaryActorTick.bCanEverTick = false;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	BuildingMeshIndex = 0;
	
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

void ACpp_BuildingVisual::SpawnBuilding() {
	if (BuildingClass && !IsHidden()) {
		GetWorld()->SpawnActor<ACpp_Building_Base>(BuildingClass, GetActorTransform());
	}
}

