// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorganSpectatorWidget.generated.h"

class UTextBlock;

UCLASS()
class MORGAN_API UMorganSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateRespawnTimer(const int32 RespawnTime);
	
protected:	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> RespawnInText;
};
