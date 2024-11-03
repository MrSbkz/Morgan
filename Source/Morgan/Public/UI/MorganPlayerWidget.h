// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganPlayerWidget.generated.h"

class UMorganHealthBarWidget;
class UProgressBar;

UCLASS()
class MORGAN_API UMorganPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMorganHealthBarWidget> HealthBar;
};
