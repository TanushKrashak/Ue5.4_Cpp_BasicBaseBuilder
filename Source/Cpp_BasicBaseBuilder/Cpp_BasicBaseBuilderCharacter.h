// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Cpp_BasicBaseBuilderCharacter.generated.h"

// Forward Declarations
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UStaticMeshComponent;
class ACpp_BuildingVisual;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACpp_BasicBaseBuilderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACpp_BasicBaseBuilderCharacter();
	

protected:
	//================================================================================================================
	// PROPERTIES & VARIABLES
	//================================================================================================================
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** BUild Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BuildAction;

	/** Destroy Build Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DestroyBuildingAction;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	bool bInBuildMode;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	ACpp_BuildingVisual* Builder;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	TSubclassOf<ACpp_BuildingVisual> BuildingClass;


	//================================================================================================================
	// FUNCTIONS
	//================================================================================================================
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	FHitResult PerformLineTrace(float Distance = 650.0f, bool DrawDebug = false);

public:
	//================================================================================================================
	// PROPERTIES & VARIABLES
	//================================================================================================================


	//================================================================================================================
	// FUNCTIONS
	//================================================================================================================		
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool GetBuildMode() const { return bInBuildMode; }
	// Setters
	UFUNCTION(BlueprintCallable, Category = "Building")
	void SetBuildMode(bool Enabled);


	UFUNCTION(BlueprintCallable, Category = "Building")
	void SpawnBuilding();
	UFUNCTION(BlueprintCallable, Category = "Building")
	void DestroyBuildingInstance();
	UFUNCTION(BlueprintCallable, Category = "Building")
	void CycleBuildingMeshThing();

};

