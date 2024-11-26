// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "MorganPlayerController.generated.h"

struct FInputActionValue;
class UMorganInputDataConfig;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MORGAN_API AMorganPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMorganInputDataConfig> InputDataConfig;

private:
	void OnGameStateChanged(EGameState GameState);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void Reload();
	void OpenBuildingMenu();
	void SetPause();
	void OpenImprovementsMenu();
};
