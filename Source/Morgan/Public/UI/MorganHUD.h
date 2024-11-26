// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "GameFramework/HUD.h"
#include "MorganHUD.generated.h"

class UMorganWeaponComponent;
class UMorganHealthComponent;
class UMorganPlayerWidget;

UCLASS()
class MORGAN_API AMorganHUD : public AHUD
{
	GENERATED_BODY()

public:
	void OpenClosedBuildingMenu(const bool IsOpened) const;
	void BindToHealthComponent(UMorganHealthComponent* HealthComponent) const;
	void BindToWeaponComponent(UMorganWeaponComponent* WeaponComponent) const;
	void UpdateRespawnTimer(const int32 RespawnTime) const;
	void OpenImprovementsMenu();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> SpectatorWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> WeaponDataWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> ImprovementsWidgetClass;

private:
	void InitWidgets();

	UUserWidget* InitOneWidget(
		const TSubclassOf<UUserWidget>& WidgetClass,
		ESlateVisibility InVisibility) const;

	void OnGameStateChanged(EGameState GameState);

	UPROPERTY()
	TMap<EGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* PlayerWidget;

	UPROPERTY()
	UUserWidget* BuildingWidget;

	UPROPERTY()
	UUserWidget* SpectatorWidget;

	UPROPERTY()
	UUserWidget* WeaponDataWidget;

	UPROPERTY()
	UUserWidget* PauseWidget;

	UPROPERTY()
	UUserWidget* ImprovementsWidget;

	UPROPERTY()
	UUserWidget* CurrentActiveWidget;

	bool IsImprovementsMenuOpened = false;
};
