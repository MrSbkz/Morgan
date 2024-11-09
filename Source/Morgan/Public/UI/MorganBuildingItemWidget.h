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
	void SetItemData(const FBuildingItemData& ItemData);
	void SetItemType(EBuildingItemType Type);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemCostText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SelectItemButton;

private:
	UFUNCTION()
	void OnButtonClicked();

	bool CanBuy() const;

	EBuildingItemType ItemType;
	int32 ItemCost;
};
