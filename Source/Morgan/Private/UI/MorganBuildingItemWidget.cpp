// Copyrights P.K.

#include "UI/MorganBuildingItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMorganBuildingItemWidget::SetItemData(const FBuildingItemData& ItemData) const
{
	ItemImage->SetBrushFromTexture(ItemData.ItemImage);
	ItemCostText->SetText(FText::FromString(FString::FromInt(ItemData.ItemCost)));
}
