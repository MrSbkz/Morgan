// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "MorganGameMode.generated.h"

UCLASS()
class MORGAN_API AMorganGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMorganGameMode();

	TArray<FBuildingItemData> GetBuildingItems() { return BuildingItems; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Building")
	TArray<FBuildingItemData> BuildingItems;
};
