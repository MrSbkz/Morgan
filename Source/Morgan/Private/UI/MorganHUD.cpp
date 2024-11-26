// Copyrights P.K.

#include "UI/MorganHUD.h"
#include "Blueprint/UserWidget.h"
#include "Game/MorganGameMode.h"
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

void AMorganHUD::OpenImprovementsMenu()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if(!PlayerController) return;
	
	if(IsImprovementsMenuOpened)
	{
		ImprovementsWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		BuildingWidget->SetVisibility(ESlateVisibility::Hidden);
		ImprovementsWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);		
	}

	IsImprovementsMenuOpened = !IsImprovementsMenuOpened;
}

void AMorganHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidgets();

	GameWidgets.Add(EGameState::Pause, PauseWidget);
	GameWidgets.Add(EGameState::InProgress, PlayerWidget);

	if(GetWorld())
	{
		if(AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnGameStateChanged.AddUObject(this, &AMorganHUD::OnGameStateChanged);
		}
	}
	CurrentActiveWidget = PlayerWidget;
}

void AMorganHUD::InitWidgets()
{
	PlayerWidget = InitOneWidget(PlayerWidgetClass, ESlateVisibility::Visible);
	BuildingWidget = InitOneWidget(BuildingWidgetClass, ESlateVisibility::Hidden);
	SpectatorWidget = InitOneWidget(SpectatorWidgetClass, ESlateVisibility::Hidden);
	WeaponDataWidget = InitOneWidget(WeaponDataWidgetClass, ESlateVisibility::HitTestInvisible);
	PauseWidget = InitOneWidget(PauseWidgetClass, ESlateVisibility::Hidden);
	ImprovementsWidget = InitOneWidget(ImprovementsWidgetClass, ESlateVisibility::Hidden);
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

void AMorganHUD::OnGameStateChanged(EGameState GameState)
{
	CurrentActiveWidget->SetVisibility(ESlateVisibility::Hidden);

	if(GameWidgets.Contains(GameState))
	{
		CurrentActiveWidget = GameWidgets[GameState];
		CurrentActiveWidget->SetVisibility(ESlateVisibility::Visible);		
	}
}
