// Copyrights P.K.

#include "UI/MorganHUD.h"
#include "Blueprint/UserWidget.h"

void AMorganHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		if (UUserWidget* PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass))
		{
			PlayerWidget->AddToViewport();
			PlayerWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
