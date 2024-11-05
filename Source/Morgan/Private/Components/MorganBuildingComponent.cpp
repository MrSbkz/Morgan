// Copyrights P.K.

#include "Components/MorganBuildingComponent.h"
#include "UI/MorganHUD.h"

void UMorganBuildingComponent::OpenCloseMenu()
{
	if (!GetOwner()) return;

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!PlayerController) return;

	const AMorganHUD* GameHUD = Cast<AMorganHUD>(PlayerController->GetHUD());
	if (!GameHUD) return;

	if (IsMenuOpened)
	{
		GameHUD->OpenClosedBuildingMenu(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		GameHUD->OpenClosedBuildingMenu(true);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}

	IsMenuOpened = !IsMenuOpened;
}
