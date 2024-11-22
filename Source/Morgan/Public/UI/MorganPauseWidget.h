// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganPauseWidget.generated.h"

class UButton;

UCLASS()
class MORGAN_API UMorganPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ContinueButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitButton;

private:
	UFUNCTION()
	void OnContinueButtonClicked();
	
	UFUNCTION()
	void OnQuitButtonClicked();
};
