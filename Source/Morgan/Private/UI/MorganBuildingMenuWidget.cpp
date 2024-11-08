// Copyrights P.K.

#include "UI/MorganBuildingMenuWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/Spacer.h"
#include "Game/MorganGameMode.h"
#include "UI/MorganBuildingItemWidget.h"

void UMorganBuildingMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseMenuButton)
	{
		CloseMenuButton->OnClicked.AddDynamic(this, &UMorganBuildingMenuWidget::OnCloseMenu);
	}

	if (GetWorld())
	{
		BuildingItemsHorizontalBox->ClearChildren();
		if (AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode()))
		{
			const TMap<EBuildingItemType, FBuildingItemData> BuildingItems = GameMode->GetBuildingItems();

			uint8 i = 0;
			for (auto BuildingItemPair : BuildingItems)
			{
				++i;
				UMorganBuildingItemWidget* BuildingItemWidget = CreateWidget<UMorganBuildingItemWidget>(
					GetWorld(),
					BuildingItemWidgetClass);

				BuildingItemWidget->SetItemData(BuildingItemPair.Value);
				BuildingItemWidget->SetItemType(BuildingItemPair.Key);
				BuildingItemsHorizontalBox->AddChild(BuildingItemWidget);

				if (i == BuildingItems.Num() - 1) continue;

				USpacer* Spacer = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
				Spacer->SetSize(FVector2D(10.0f, 1.0f));
				BuildingItemsHorizontalBox->AddChild(Spacer);
			}
		}
	}
}

void UMorganBuildingMenuWidget::OnCloseMenu()
{
	const APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn) return;

	if (UMorganBuildingComponent* BuildingComponent = Pawn->FindComponentByClass<UMorganBuildingComponent>())
	{
		BuildingComponent->OpenCloseMenu();
	}
}
