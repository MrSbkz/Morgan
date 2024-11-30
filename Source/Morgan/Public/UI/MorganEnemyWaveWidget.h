// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganEnemyWaveWidget.generated.h"

class UTextBlock;

UCLASS()
class MORGAN_API UMorganEnemyWaveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentWaveText;
};
