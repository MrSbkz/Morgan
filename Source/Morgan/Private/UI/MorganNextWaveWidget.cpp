// Copyrights P.K.

#include "UI/MorganNextWaveWidget.h"
#include "Components/TextBlock.h"
#include "Game/MorganGameMode.h"

void UMorganNextWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
	if (GetWorld())
	{
		if (AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnNextWaveTimeUpdated.AddLambda([&](const int32 NextWave)
			{
				if(NextWave > 0)
				{
					SetVisibility(ESlateVisibility::HitTestInvisible);
					NextWaveInText->SetText(FText::FromString(FString::FromInt(NextWave)));					
				}
				else
				{
					SetVisibility(ESlateVisibility::Hidden);
				}
			});
		}
	}
}
