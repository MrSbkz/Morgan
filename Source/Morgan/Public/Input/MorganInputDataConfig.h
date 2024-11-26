// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MorganInputDataConfig.generated.h"


class UInputAction;

UCLASS()
class MORGAN_API UMorganInputDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PistolReload;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* OpenBuildingMenu;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* Pause;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* OpenImprovementsMenu;
};
