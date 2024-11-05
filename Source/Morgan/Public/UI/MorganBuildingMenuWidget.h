// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganBuildingMenuWidget.generated.h"

class UMorganBuildingItemWidget;
class UButton;
class UHorizontalBox;

UCLASS()
class MORGAN_API UMorganBuildingMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> BuildingItemsHorizontalBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseMenuButton;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMorganBuildingItemWidget> BuildingItemWidgetClass;

private:
	UFUNCTION()
	void OnCloseMenu();
};
