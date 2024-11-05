#pragma once

#include "MorganCoreTypes.generated.h"

USTRUCT()
struct FBuildingItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Building")
	int32 ItemCost = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Building")
	UTexture2D* ItemImage = nullptr;
};
