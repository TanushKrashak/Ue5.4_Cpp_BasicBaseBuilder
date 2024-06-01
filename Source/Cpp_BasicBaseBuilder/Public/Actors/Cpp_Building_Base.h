// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_Building_Base.generated.h"

// Forward Declarations
class UInstancedStaticMeshComponent;

UCLASS()
class CPP_BASICBASEBUILDER_API ACpp_Building_Base : public AActor
{
	GENERATED_BODY()
	
public:
	ACpp_Building_Base();

protected:
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	UInstancedStaticMeshComponent* FoundationInstancedMesh;

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
	UFUNCTION(BlueprintCallable, Category = "Building")
	void DestroyInstance(FVector HitPoint);
		
	UFUNCTION(BlueprintCallable, Category = "Building")
	FTransform GetInstancedSocketTransform(UInstancedStaticMeshComponent* InstancedComp, int32 InstanceIndex, const FName& SocketName);

	
	

	
};
