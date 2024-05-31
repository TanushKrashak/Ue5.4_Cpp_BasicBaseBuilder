// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_Building_Base.h"
#include "Components/InstancedStaticMeshComponent.h"


ACpp_Building_Base::ACpp_Building_Base() {
	PrimaryActorTick.bCanEverTick = false;
	
	// Create the instanced mesh component and set it as the root component
	FoundationInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FoundationInstancedMesh"));
	RootComponent = FoundationInstancedMesh;

}

void ACpp_Building_Base::BeginPlay() {
	Super::BeginPlay();
	// Empty transform to start with
	FTransform MeshTransform = FTransform();
	// Add 3 instances of the mesh
	for (uint8 i = 0; i < 3; i++) {
		FoundationInstancedMesh->AddInstance(FTransform(MeshTransform));
		FVector MeshLocation = MeshTransform.GetLocation();
		MeshLocation.Z += 250;

		MeshTransform.SetLocation(MeshLocation);
	}
}

