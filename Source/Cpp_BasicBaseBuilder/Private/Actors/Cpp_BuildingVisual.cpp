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

	if (BuildingMeshes[BuildingMeshIndex]) {
		BuildingMesh->SetStaticMesh(BuildingMeshes[BuildingMeshIndex]);

	}
	
}

ACpp_Building_Base* ACpp_BuildingVisual::GetHitBuildingActor(const FHitResult& HitResult) {
	return Cast<ACpp_Building_Base>(HitResult.GetActor());
}

void ACpp_BuildingVisual::SetBuildPosition(const FHitResult HitResult) {
	if (HitResult.bBlockingHit) {
		SetActorHiddenInGame(false);		

		if (ACpp_Building_Base* HitBuilding = GetHitBuildingActor(HitResult)) {
			FTransform SocketTransform = HitBuilding->GetHitSocketTransform(HitResult);
			if (!SocketTransform.Equals(FTransform())) {
				SetActorTransform(SocketTransform);
				return;
			}
			else {
				SetActorLocation(HitResult.Location);
			}
		}			
		else {
			SetActorLocation(HitResult.Location);
		}
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

void ACpp_BuildingVisual::CycleMesh() {
	if (++BuildingMeshIndex >= BuildingMeshes.Num()) {
		BuildingMeshIndex = 0;
	}
	if (BuildingMeshes[BuildingMeshIndex]) {
		BuildingMesh->SetStaticMesh(BuildingMeshes[BuildingMeshIndex]);

	}
}

