// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "Cpp_BuildingVisual.generated.h"


// Forward Declarations
class UStaticMeshComponent;
class ACpp_Building_Base;
class UStaticMesh;
class UMaterialInstance;

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
	TArray<FBuildingVisualType> BuildTypes;

	uint8 BuildingMeshIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UMaterialInstance* MaterialFalse;
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UMaterialInstance* MaterialTrue;

	bool bMaterialIsTrue;

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
