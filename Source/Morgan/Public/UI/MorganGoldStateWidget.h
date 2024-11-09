// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganGoldStateWidget.generated.h"

class UTextBlock;

UCLASS()
class MORGAN_API UMorganGoldStateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> GoldAmountText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> IncomeText;
	
	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* IncomeAnimation;
};
