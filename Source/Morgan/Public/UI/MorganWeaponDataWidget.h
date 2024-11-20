// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganWeaponDataWidget.generated.h"

class UMorganWeaponComponent;
class UTextBlock;

UCLASS()
class MORGAN_API UMorganWeaponDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToWeaponComponent(const UMorganWeaponComponent* WeaponComponent) const;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BulletsLeftText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BulletsAmountText;
};
