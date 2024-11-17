// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganMainBuildingHealthWidget.generated.h"

class UMorganHealthBarWidget;

UCLASS()
class MORGAN_API UMorganMainBuildingHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMorganHealthBarWidget> HealthBar;
};
