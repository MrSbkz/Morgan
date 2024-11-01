// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MorganHUD.generated.h"

class UMorganPlayerWidget;

UCLASS()
class MORGAN_API AMorganHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
};
