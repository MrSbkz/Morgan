// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MorganPlayerController.generated.h"

struct FInputActionValue;
class UMorganInputDataConfig;
class UInputMappingContext;
class UInputAction;
class UInputMappingContext;

UCLASS()
class MORGAN_API AMorganPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMorganInputDataConfig> InputDataConfig;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void Reload();
	void OpenBuildingMenu();
};
