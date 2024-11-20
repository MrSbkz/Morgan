// Copyrights P.K.

#include "UI/MorganHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/MorganPlayerWidget.h"
#include "UI/MorganSpectatorWidget.h"
#include "UI/MorganWeaponDataWidget.h"

void AMorganHUD::OpenClosedBuildingMenu(const bool IsOpened) const
{
	if (!BuildingWidget) return;

	if (IsOpened)
	{
		BuildingWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BuildingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMorganHUD::BindToHealthComponent(UMorganHealthComponent* HealthComponent) const
{
	if (!PlayerWidget) return;

	if (const UMorganPlayerWidget* MorganPlayerWidget = Cast<UMorganPlayerWidget>(PlayerWidget))
	{
		MorganPlayerWidget->BindToHealthComponent(HealthComponent);
	}
}

void AMorganHUD::BindToWeaponComponent(UMorganWeaponComponent* WeaponComponent) const
{
	if(!WeaponDataWidget) return;

	if(UMorganWeaponDataWidget* MorganWeaponDataWidget = Cast<UMorganWeaponDataWidget>(WeaponDataWidget))
	{
		MorganWeaponDataWidget->BindToWeaponComponent(WeaponComponent);
	}
}

void AMorganHUD::UpdateRespawnTimer(const int32 RespawnTime) const
{
	if (!SpectatorWidget) return;

	if (RespawnTime == 0)
	{
		SpectatorWidget->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	SpectatorWidget->SetVisibility(ESlateVisibility::Visible);
	if (UMorganSpectatorWidget* MorganSpectatorWidget = Cast<UMorganSpectatorWidget>(SpectatorWidget))
	{
		MorganSpectatorWidget->UpdateRespawnTimer(RespawnTime);
	}
}

void AMorganHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidgets();
}

void AMorganHUD::InitWidgets()
{
	PlayerWidget = InitOneWidget(PlayerWidgetClass, ESlateVisibility::Visible);
	BuildingWidget = InitOneWidget(BuildingWidgetClass, ESlateVisibility::Hidden);
	SpectatorWidget = InitOneWidget(SpectatorWidgetClass, ESlateVisibility::Hidden);
	WeaponDataWidget = InitOneWidget(WeaponDataWidgetClass, ESlateVisibility::HitTestInvisible);
}

UUserWidget* AMorganHUD::InitOneWidget(
	const TSubclassOf<UUserWidget>& WidgetClass,
	const ESlateVisibility InVisibility) const
{
	if (!WidgetClass) return nullptr;

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		Widget->SetVisibility(InVisibility);
	}

	return Widget;
}
