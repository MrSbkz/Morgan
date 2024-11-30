// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganNextWaveWidget.generated.h"

class UTextBlock;

UCLASS()
class MORGAN_API UMorganNextWaveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NextWaveInText;
};
