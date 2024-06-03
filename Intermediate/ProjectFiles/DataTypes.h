#pragma once

#include "DataTypes.generated.h"

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

