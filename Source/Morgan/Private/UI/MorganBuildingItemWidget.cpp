// Copyrights P.K.

#include "UI/MorganBuildingItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/TextBlock.h"
#include "Player/MorganPlayerState.h"

void UMorganBuildingItemWidget::SetItemData(const FBuildingItemData& ItemData)
{
	ItemImage->SetBrushFromTexture(ItemData.ItemImage);
	ItemCostText->SetText(FText::FromString(FString::FromInt(ItemData.ItemCost)));
	ItemCost = ItemData.ItemCost;

	if (!CanBuy())
	{
		ItemCostText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}
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

	if (CanBuy())
	{
		BuildingComponent->StartBuilding(ItemType);
	}
}

bool UMorganBuildingItemWidget::CanBuy() const
{
	const AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(GetOwningPlayerState());
	return PlayerState && PlayerState->GetGoldAmount() >= ItemCost;
}
