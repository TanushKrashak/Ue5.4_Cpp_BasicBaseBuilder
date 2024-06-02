// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_BuildingVisual.generated.h"
#include "Components/StaticMeshComponent.h"

// Forward Declarations


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

	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================	
	virtual void BeginPlay() override;		


public:
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================


	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================
	void SetBuildPosition(FHitResult& HitResult);

	
};
