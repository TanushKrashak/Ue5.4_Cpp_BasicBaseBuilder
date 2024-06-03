// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_BuildingVisual.generated.h"


// Forward Declarations
class UStaticMeshComponent;
class ACpp_Building_Base;
class UStaticMesh;

UCLASS()
class CPP_BASICBASEBUILDER_API ACpp_BuildingVisual : public AActor
{
	GENERATED_BODY()

public:	
	ACpp_BuildingVisual();

protected:
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ACpp_Building_Base> BuildingClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TArray<UStaticMesh*> BuildingMeshes;

	uint8 BuildingMeshIndex;

	

	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================	
	virtual void BeginPlay() override;		

	ACpp_Building_Base* GetHitBuildingActor(const FHitResult& HitResult);

public:
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================


	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================
	void SetBuildPosition(const FHitResult HitResult);
	void SpawnBuilding();
	void CycleMesh();
};
