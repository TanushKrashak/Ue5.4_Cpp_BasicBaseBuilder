// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_Building_Base.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


ACpp_Building_Base::ACpp_Building_Base() {
	PrimaryActorTick.bCanEverTick = false;
	
	// Create the instanced mesh component and set it as the root component
	FoundationInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FoundationInstancedMesh"));
	RootComponent = FoundationInstancedMesh;

	WallInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallInstancedMesh"));
}

void ACpp_Building_Base::BeginPlay() {
	Super::BeginPlay();
	// Spawn the building at the location of the actor
	FoundationInstancedMesh->AddInstance(FTransform());
	// Set its transform to the actor's transform
	FoundationInstancedMesh->SetWorldTransform(GetActorTransform());
	
}

void ACpp_Building_Base::DestroyInstance(FVector HitPoint) {
	const TArray<int32> HitIndexes = FoundationInstancedMesh->GetInstancesOverlappingSphere(HitPoint, 1.0f);

	if (HitIndexes.Num() > 0) {
		FoundationInstancedMesh->RemoveInstance(HitIndexes[0]);
	}
}

FTransform ACpp_Building_Base::GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComp, int32 InstanceIndex, 
														   const FName& SocketName, bool& Success, bool WorldSpace) {
	// Set the success to false by default
	Success = true;
	// Check if the instanced component & instance index are valid
	if (InstancedComp && InstancedComp->IsValidInstance(InstanceIndex)) {
		
		FTransform InstanceTransform = FTransform();		
		
		// Set the instance transform based on the instance index (false for component space)
		InstancedComp->GetInstanceTransform(InstanceIndex, InstanceTransform, false);

		// RTS_Component is used to get the socket transform in the component space
		FTransform SocketTransform = InstancedComp->GetSocketTransform(SocketName, RTS_Component);

		// Check if the socket transform is equal to the default transform, if so return false
		if (SocketTransform.Equals(FTransform())) {
			Success = false;
			return FTransform();
		}

		FTransform RelativeTransform = UKismetMathLibrary::MakeRelativeTransform(SocketTransform, InstanceTransform);

		FVector RelativeLocation = RelativeTransform.GetLocation();
		// This is for when spawning actors rather than components so it will be in world space rather than component space
		if (WorldSpace) {
			RelativeLocation.Z = SocketTransform.GetLocation().Z;
			// True for world space so we can get the world location of the instance
			InstancedComp->GetInstanceTransform(InstanceIndex, InstanceTransform, true);
			FVector WorldLocation = InstanceTransform.GetLocation() + RelativeLocation;
			RelativeTransform.SetLocation(WorldLocation);
			return RelativeTransform;
		}
		// This is for when spawning components so it will be in component space

		RelativeLocation.Z = InstanceTransform.GetLocation().Z + SocketTransform.GetLocation().Z;
		// Change the Z value of Relative Transform to be the sum of the Z values of the Instance and Socket transforms
		RelativeTransform.SetLocation(RelativeLocation);
		return RelativeTransform;
	}
	Success = false;
	return FTransform();
}

int32 ACpp_Building_Base::GetHitIndex(const FHitResult& HitResult) {
	TArray<int32> HitIndexes = FoundationInstancedMesh->GetInstancesOverlappingSphere(HitResult.Location, 2.0f);
	if (HitIndexes.Num()) {
		return HitIndexes[0];
	}
	return -1;
}

