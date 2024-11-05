// Copyrights P.K.

#include "UI/MorganHUD.h"
#include "Blueprint/UserWidget.h"

void AMorganHUD::OpenClosedBuildingMenu(const bool IsOpened) const
{
	if (!BuildingWidget) return;

	if (IsOpened)
	{
		BuildingWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BuildingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMorganHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidgets();
}

void AMorganHUD::InitWidgets()
{
	if (PlayerWidgetClass)
	{
		if (UUserWidget* PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass))
		{
			PlayerWidget->AddToViewport();
			PlayerWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (BuildingWidgetClass)
	{
		BuildingWidget = CreateWidget<UUserWidget>(GetWorld(), BuildingWidgetClass);
		if (BuildingWidget)
		{
			BuildingWidget->AddToViewport();
			BuildingWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
