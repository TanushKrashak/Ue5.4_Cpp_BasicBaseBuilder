// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cpp_Building_Base.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"



ACpp_Building_Base::ACpp_Building_Base() {
	PrimaryActorTick.bCanEverTick = false;
	
	// Create the instanced mesh component and set it as the root component
	FoundationInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FoundationInstancedMesh"));
	RootComponent = FoundationInstancedMesh;

	WallInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallInstancedMesh"));
	CeilingInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CeilingInstancedMesh"));
}

void ACpp_Building_Base::BeginPlay() {
	Super::BeginPlay();
	// Spawn the building at the location of the actor
	FoundationInstancedMesh->AddInstance(FTransform());
	// Set its transform to the actor's transform
	FoundationInstancedMesh->SetWorldTransform(GetActorTransform());
	
	// Get all the socket names of the instanced mesh component
	MeshInstanceSockets = FoundationInstancedMesh->GetAllSocketNames();
	MeshInstanceSockets.Append(WallInstancedMesh->GetAllSocketNames());
	MeshInstanceSockets.Append(CeilingInstancedMesh->GetAllSocketNames());

	FInstanceSocketCheck InstanceSocket;
	// Add all the instanced mesh components to the InstanceSocketCheck array
	InstanceSocket.InstancedComponent = FoundationInstancedMesh;
	InstanceSocketCheck.Add(InstanceSocket);
	InstanceSocket.InstancedComponent = WallInstancedMesh;
	InstanceSocketCheck.Add(InstanceSocket);
	InstanceSocket.InstancedComponent = CeilingInstancedMesh;
	InstanceSocketCheck.Add(InstanceSocket);
}

bool ACpp_Building_Base::IsValidSocket(UInstancedStaticMeshComponent* HitComp, const FName Filter, const FName& SocketName) {
	bool bSuccess = true;
	if (!HitComp->DoesSocketExist(SocketName)) {
		bSuccess = false;
		return bSuccess;
	}
	// Check if socketName contains the filter
	if (!SocketName.ToString().Contains(Filter.ToString(), ESearchCase::CaseSensitive)) {
		bSuccess = false;
		return bSuccess;
	}
	return true;
}

void ACpp_Building_Base::DestroyInstance(FVector HitPoint) {
	const TArray<int32> HitIndexes = FoundationInstancedMesh->GetInstancesOverlappingSphere(HitPoint, 1.0f);

	if (HitIndexes.Num() > 0) {
		FoundationInstancedMesh->RemoveInstance(HitIndexes[0]);
	}
}

FTransform ACpp_Building_Base::GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComp, int32 InstanceIndex, const FName& SocketName) {	
	if (InstancedComp && InstancedComp->IsValidInstance(InstanceIndex)) {
		FTransform InstanceTransform = FTransform();				
		InstancedComp->GetInstanceTransform(InstanceIndex, InstanceTransform, true);
		FTransform SocketTransform = InstancedComp->GetSocketTransform(SocketName, RTS_Component);
		InstanceTransform = SocketTransform * InstanceTransform;

		// DEBUGGING DRAW FUNCTIONS
		DrawDebugString(GetWorld(), InstanceTransform.GetLocation(), SocketName.ToString(), nullptr, FColor::White, 5.0f, true);
		DrawDebugSphere(GetWorld(), InstanceTransform.GetLocation(), 5.0f, 10, FColor::Red);
		FTransform temp;
		InstancedComp->GetInstanceTransform(InstanceIndex, temp, true);
		DrawDebugSphere(GetWorld(), temp.GetLocation(), 5.0f, 15, FColor::Blue);


		return InstanceTransform;
	}
	return FTransform();
	// OLD CODE (KEEPING FOR REFERENCE)
	/*
	// Check if the instanced component & instance index are valid
	if (InstancedComp && InstancedComp->IsValidInstance(InstanceIndex)) {
		
		FTransform InstanceTransform = FTransform();		
		
		// Set the instance transform based on the instance index (false for component space)
		InstancedComp->GetInstanceTransform(InstanceIndex, InstanceTransform, false);

		// RTS_Component is used to get the socket transform in the component space
		FTransform SocketTransform = InstancedComp->GetSocketTransform(SocketName, RTS_Component);

		// Check if the socket transform is equal to the default transform, if so return false
		if (SocketTransform.Equals(FTransform())) {
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
	return FTransform();
	*/
}

int32 ACpp_Building_Base::GetHitIndex(const FHitResult& HitResult) {
	return HitResult.Item;
}

FBuildingSocketData ACpp_Building_Base::GetHitSocketTransform(const FHitResult& HitResult, const FName& Filter, float ValidHitDistance) {

	// Create a new instance of the FBuildingSocketData struct which will hold the socket data
	FBuildingSocketData SocketData = FBuildingSocketData();

	if (UInstancedStaticMeshComponent* HitComp = Cast<UInstancedStaticMeshComponent>(HitResult.GetComponent())) {
		int32 HitIndex = GetHitIndex(HitResult);
		if (HitIndex != -1) {
			// Loop through all the socket names of the instanced mesh component
			for (const FName& SocketName : MeshInstanceSockets) {
				// Check if the socket is valid
				if (IsValidSocket(HitComp, Filter, SocketName)) {
					FTransform SocketTransform = GetInstancedSocketTransform(HitComp, HitIndex, SocketName);
					// if distance is <= ValidHitDistance, set the socket data and return it
					if (FVector::Distance(SocketTransform.GetLocation(), HitResult.Location) <= ValidHitDistance) {
						SocketData.Index = HitIndex;
						SocketData.InstancedComponent = HitComp;
						SocketData.SocketName = SocketName;
						SocketData.SocketTransform = SocketTransform;
						return SocketData;
					}
				}
			}

		}
	}
	return SocketData;
}

void ACpp_Building_Base::AddInstance(const FBuildingSocketData& BuildingSocketData, EBuildType BuildType) {

	switch (BuildType) {
		case EBuildType::Foundation:
			FoundationInstancedMesh->AddInstance(BuildingSocketData.SocketTransform, true);
			break;
		case EBuildType::Wall:
			WallInstancedMesh->AddInstance(BuildingSocketData.SocketTransform, true);
			break;
		case EBuildType::Ceiling:
			CeilingInstancedMesh->AddInstance(BuildingSocketData.SocketTransform, true);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Invalid Build Type"));
			break;
	}
	
	
}


