// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganWeaponDataWidget.generated.h"


class UTextBlock;

UCLASS()
class MORGAN_API UMorganWeaponDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BulletsLeftText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BulletsAmountText;
};
