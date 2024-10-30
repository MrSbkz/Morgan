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
};
