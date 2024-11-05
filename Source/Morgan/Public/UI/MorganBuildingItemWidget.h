// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "MorganBuildingItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class MORGAN_API UMorganBuildingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemData(const FBuildingItemData& ItemData) const;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemCostText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SelectItemButton;
};
