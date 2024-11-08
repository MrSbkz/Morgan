// Copyrights P.K.

#include "UI/MorganBuildingItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/TextBlock.h"

void UMorganBuildingItemWidget::SetItemData(const FBuildingItemData& ItemData) const
{
	ItemImage->SetBrushFromTexture(ItemData.ItemImage);
	ItemCostText->SetText(FText::FromString(FString::FromInt(ItemData.ItemCost)));
}

void UMorganBuildingItemWidget::SetItemType(const EBuildingItemType Type)
{
	ItemType = Type;
}

void UMorganBuildingItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectItemButton->OnClicked.AddDynamic(this, &UMorganBuildingItemWidget::OnButtonClicked);
}

void UMorganBuildingItemWidget::OnButtonClicked()
{
	const APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn) return;

	UMorganBuildingComponent* BuildingComponent = Pawn->FindComponentByClass<UMorganBuildingComponent>();
	if (!BuildingComponent) return;

	BuildingComponent->StartBuilding(ItemType);
}
