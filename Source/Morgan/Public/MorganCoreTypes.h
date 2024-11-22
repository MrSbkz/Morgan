#pragma once

#include "MorganCoreTypes.generated.h"

class AMorganBuildingActorBase;

UENUM(BlueprintType)
enum class EBuildingItemType : uint8
{
	None,
	Cannon,
	Barrel
};

USTRUCT()
struct FBuildingItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Building")
	int32 ItemCost = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Building")
	TObjectPtr<UTexture2D> ItemImage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="Building")
	TSubclassOf<AMorganBuildingActorBase> BuildingItemClass;
};

UENUM()
enum class EGameState : uint8
{
	Pause,
	InProgress
};
