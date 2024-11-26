// Copyrights P.K.

#include "UI/MorganImprovementsMenuWidget.h"
#include "Components/Button.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "Components/TextBlock.h"
#include "Player/MorganPlayerState.h"

void UMorganImprovementsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!GetOwningPlayer()) return;

	ImproveWeaponDamageButton->OnClicked.AddDynamic(this, &UMorganImprovementsMenuWidget::ImproveWeaponDamage);
	ImprovePlayerHealthButton->OnClicked.AddDynamic(this, &UMorganImprovementsMenuWidget::ImprovePlayerHealth);

	AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(GetOwningPlayerState());
	if (!PlayerState) return;

	PlayerState->OnGoldAmountChanged.AddUObject(this, &UMorganImprovementsMenuWidget::OnPlayerGoldAmountChanged);

	SetWeaponDamageData(PlayerState);
	SetPlayerHealthData(PlayerState);
}

void UMorganImprovementsMenuWidget::OnPlayerGoldAmountChanged(const int32 GoldAmount, const int32 GoldDelta)
{
	SetCostData(GoldAmount >= WeaponImprovementCost, ImproveWeaponDamageButton, ImproveDamageCostText);
	SetCostData(GoldAmount >= HealthImprovementCost, ImprovePlayerHealthButton, ImproveHealthCostText);
}

void UMorganImprovementsMenuWidget::ImproveWeaponDamage()
{
	AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(GetOwningPlayerState());
	if (!PlayerState) return;

	PlayerState->AddGold(-WeaponImprovementCost);
	PlayerState->IncreaseWeaponLevel();
	SetWeaponDamageData(PlayerState);
}

void UMorganImprovementsMenuWidget::ImprovePlayerHealth()
{
	AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(GetOwningPlayerState());
	if (!PlayerState) return;

	PlayerState->AddGold(-HealthImprovementCost);
	PlayerState->IncreaseHealthLevel();
	SetPlayerHealthData(PlayerState);
}

void UMorganImprovementsMenuWidget::SetWeaponDamageData(const AMorganPlayerState* PlayerState)
{
	const UMorganWeaponComponent* WeaponComponent = GetOwningPlayerPawn()->FindComponentByClass<UMorganWeaponComponent>();
	if (!WeaponComponent) return;

	CurrentWeaponDamageText->SetText(FText::FromString(FString::FromInt(WeaponComponent->GetWeaponDamageAmount())));

	WeaponImprovementCost = WeaponComponent->GetWeaponImprovementCost();
	ImproveDamageCostText->SetText(FText::FromString(FString::FromInt(WeaponImprovementCost)));

	const int32 PlayerGoldAmount = PlayerState->GetGoldAmount();
	SetCostData(PlayerGoldAmount >= WeaponImprovementCost, ImproveWeaponDamageButton, ImproveDamageCostText);
}

void UMorganImprovementsMenuWidget::SetPlayerHealthData(const AMorganPlayerState* PlayerState)
{
	const UMorganHealthComponent* HealthComponent = GetOwningPlayerPawn()->FindComponentByClass<UMorganHealthComponent>();
	if (!HealthComponent) return;

	CurrentHealthText->SetText(FText::FromString(FString::FromInt(HealthComponent->GetMaxHealth())));

	HealthImprovementCost = HealthComponent->GetHealthImprovementCost();
	ImproveHealthCostText->SetText(FText::FromString(FString::FromInt(HealthImprovementCost)));

	const int32 PlayerGoldAmount = PlayerState->GetGoldAmount();
	SetCostData(PlayerGoldAmount >= HealthImprovementCost, ImprovePlayerHealthButton, ImproveHealthCostText);
}

void UMorganImprovementsMenuWidget::SetCostData(const bool CanBuy, UButton* Button, UTextBlock* Text)
{
	if (CanBuy)
	{
		Text->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		Button->SetIsEnabled(true);
	}
	else
	{
		Text->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		Button->SetIsEnabled(false);
	}
}
