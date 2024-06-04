// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cpp_Building_Base.generated.h"

// Forward Declarations
class UInstancedStaticMeshComponent;
enum class EBuildType : uint8;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	UInstancedStaticMeshComponent* WallInstancedMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	UInstancedStaticMeshComponent* CeilingInstancedMesh;

	TArray<FName> MeshInstanceSockets;

	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================	
	virtual void BeginPlay() override;

	bool IsValidSocket(UInstancedStaticMeshComponent* HitComp, const FName Filter, const FName& SocketName);

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

	int32 GetHitIndex(const FHitResult& HitResult);
	
	FTransform GetHitSocketTransform(const FHitResult& HitResult, const FName& Filter, float ValidHitDistance = 100.0f);
	
	void AddInstance(const FTransform ActorTransform, EBuildType BuildType);
};

