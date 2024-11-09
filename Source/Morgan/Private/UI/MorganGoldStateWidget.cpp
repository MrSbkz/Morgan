// Copyrights P.K.

#include "UI/MorganGoldStateWidget.h"
#include "Components/TextBlock.h"
#include "Player/MorganPlayerState.h"

void UMorganGoldStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(GetOwningPlayerState());
	if (!PlayerState) return;

	GoldAmountText->SetText(FText::FromString(FString::FromInt(0)));
	IncomeText->SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)));

	PlayerState->OnGoldAmountChanged.AddLambda([this](const int32 GoldAmount, const int32 Income)
	{
		GoldAmountText->SetText(FText::FromString(FString::FromInt(GoldAmount)));

		const bool IsIncomePositive = Income >= 0.0f;
		const FString IncomeString = FString::Printf(TEXT("%hs%i"), IsIncomePositive ? "+" : "", Income);

		IncomeText->SetText(FText::FromString(IncomeString));
		if (IsIncomePositive)
		{
			IncomeText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		}
		else
		{
			IncomeText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		}

		PlayAnimation(IncomeAnimation);
	});
}
