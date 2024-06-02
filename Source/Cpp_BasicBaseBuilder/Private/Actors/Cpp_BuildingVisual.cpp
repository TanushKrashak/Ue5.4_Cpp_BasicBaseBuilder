// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_BuildingVisual.h"


ACpp_BuildingVisual::ACpp_BuildingVisual() {
	PrimaryActorTick.bCanEverTick = false;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;
}

void ACpp_BuildingVisual::BeginPlay() {
	Super::BeginPlay();
	
	
}

void ACpp_BuildingVisual::SetBuildPosition(const FHitResult& HitResult) {

}

