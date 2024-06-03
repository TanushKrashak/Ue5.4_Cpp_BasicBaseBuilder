// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_BuildingVisual.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/Cpp_Building_Base.h"



ACpp_BuildingVisual::ACpp_BuildingVisual() {
	PrimaryActorTick.bCanEverTick = false;

	BuildingMeshThing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMeshThing"));
	RootComponent = BuildingMeshThing;

	BuildingTypeIndex = 0;
	
	bMaterialIsTrue = false;
}

void ACpp_BuildingVisual::BeginPlay() {
	Super::BeginPlay();
	
	SetActorHiddenInGame(true);

	if (BuildTypes[BuildingTypeIndex].BuildingMesh) {
		BuildingMeshThing->SetStaticMesh(BuildTypes[BuildingTypeIndex].BuildingMesh);

	}
	// On start, set the material to the can place material
	if (MaterialTrue) {
		bMaterialIsTrue = true;
		BuildingMeshThing->SetMaterial(0, MaterialTrue);
	}
}

ACpp_Building_Base* ACpp_BuildingVisual::GetHitBuildingActor(const FHitResult& HitResult) {
	return Cast<ACpp_Building_Base>(HitResult.GetActor());
}

void ACpp_BuildingVisual::SetBuildPosition(const FHitResult HitResult) {
	// If we hit something
	if (HitResult.bBlockingHit) {
		SetActorHiddenInGame(false);		
		InteractingBuilding = GetHitBuildingActor(HitResult);
		// If we hit a building
		if (InteractingBuilding) {
			FTransform SocketTransform = InteractingBuilding->GetHitSocketTransform(HitResult);
			// If socket transform was changed
			if (!SocketTransform.Equals(FTransform())) {
				SetActorTransform(SocketTransform);
				// Set the material to the true material
				if (MaterialTrue && !bMaterialIsTrue) {
					bMaterialIsTrue = true;
					BuildingMeshThing->SetMaterial(0, MaterialTrue);
				}
				return;
			}
			else {
				if (MaterialFalse && bMaterialIsTrue) {
					bMaterialIsTrue = false;
					BuildingMeshThing->SetMaterial(0, MaterialFalse);
				}
				SetActorLocation(HitResult.Location);
			}
		}			
		else {
			SetActorLocation(HitResult.Location);
		}
	}	
	else {
		// If we didn't hit anything, hide the actor
		InteractingBuilding = nullptr;
		SetActorHiddenInGame(true);
	}
}

void ACpp_BuildingVisual::SpawnBuilding() {
	if (BuildingClass && !IsHidden()) {
		GetWorld()->SpawnActor<ACpp_Building_Base>(BuildingClass, GetActorTransform());
	}
}	

void ACpp_BuildingVisual::CycleMesh() {
	if (++BuildingTypeIndex >= BuildTypes.Num()) {
		BuildingTypeIndex = 0;
	}
	if (BuildTypes[BuildingTypeIndex].BuildingMesh) {
		BuildingMeshThing->SetStaticMesh(BuildTypes[BuildingTypeIndex].BuildingMesh);

	}
}

