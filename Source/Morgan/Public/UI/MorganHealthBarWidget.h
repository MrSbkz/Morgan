// Copyrights P.K.

#pragma once

#include "Runtime/CoreUObject/Public/UObject/ObjectPtr.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MorganHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class MORGAN_API UMorganHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealth(float HealthPercent) const;

protected:	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	FLinearColor GreenColor = FLinearColor(0.0f, 0.4f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category="UI")
	FLinearColor RedColor = FLinearColor(0.4f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category="UI")
	FLinearColor YellowColor = FLinearColor(0.7f, 0.5f, 0.0f);
};


