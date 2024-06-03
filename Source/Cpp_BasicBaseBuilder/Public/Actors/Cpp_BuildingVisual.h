// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_BuildingVisual.generated.h"


// Forward Declarations
class UStaticMeshComponent;
class ACpp_Building_Base;
class UStaticMesh;
class UMaterialInstance;

UENUM(BlueprintType)
enum class EBuildType : uint8 {
	Foundation	UMETA(DisplayName = "Foundation"),
	Wall		UMETA(DisplayName = "Wall"),
};

USTRUCT(BlueprintType)
struct FBuildingVisualType {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	class UStaticMesh* BuildingMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	EBuildType BuildType;
};

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
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UStaticMeshComponent* BuildingMeshThing;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ACpp_Building_Base> BuildingClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TArray<FBuildingVisualType> BuildTypes;

	uint8 BuildingTypeIndex;

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
