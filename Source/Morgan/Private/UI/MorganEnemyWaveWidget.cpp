// Copyrights P.K.

#include "UI/MorganEnemyWaveWidget.h"
#include "Components/TextBlock.h"
#include "Game/MorganGameMode.h"

void UMorganEnemyWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetWorld())
	{
		if (AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnCurrentWaveUpdated.AddLambda([&](const int32 CurrentWave)
			{
				CurrentWaveText->SetText(FText::FromString(FString::FromInt(CurrentWave)));
			});
		}
	}
}
