// Copyrights P.K.

#include "UI/MorganSpectatorWidget.h"
#include "Components/TextBlock.h"

void UMorganSpectatorWidget::UpdateRespawnTimer(const int32 RespawnTime)
{	
	SetVisibility(ESlateVisibility::Visible);
	const FString RespawnInString = FString::Printf(TEXT("Respawn in: %i"), RespawnTime);
	RespawnInText->SetText(FText::FromString(RespawnInString));
}

