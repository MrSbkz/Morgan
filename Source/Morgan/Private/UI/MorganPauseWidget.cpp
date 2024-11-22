// Copyrights P.K.

#include "UI/MorganPauseWidget.h"
#include "Components/Button.h"
#include "Game/MorganGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

void UMorganPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ContinueButton->OnClicked.AddDynamic(this, &UMorganPauseWidget::OnContinueButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMorganPauseWidget::OnQuitButtonClicked);
}

void UMorganPauseWidget::OnContinueButtonClicked()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UMorganPauseWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
