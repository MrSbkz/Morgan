// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganImprovementsMenuWidget.generated.h"

class AMorganPlayerState;
class UTextBlock;
class UMorganHealthComponent;
class UMorganWeaponComponent;
class UButton;

UCLASS()
class MORGAN_API UMorganImprovementsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ImproveWeaponDamageButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentWeaponDamageText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ImproveDamageCostText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ImprovePlayerHealthButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentHealthText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ImproveHealthCostText;

private:
	void OnPlayerGoldAmountChanged(const int32 GoldAmount, const int32 GoldDelta);

	UFUNCTION()
	void ImproveWeaponDamage();

	UFUNCTION()
	void ImprovePlayerHealth();

	void SetWeaponDamageData(const AMorganPlayerState* PlayerState);
	void SetPlayerHealthData(const AMorganPlayerState* PlayerState);
	static void SetCostData(bool CanBuy, UButton* Button, UTextBlock* Text);

	int32 WeaponImprovementCost = 0;
	int32 HealthImprovementCost = 0;
};
