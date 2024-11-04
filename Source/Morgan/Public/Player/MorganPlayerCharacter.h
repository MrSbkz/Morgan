// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Player/MorganCharacterBase.h"
#include "MorganPlayerCharacter.generated.h"

class UMorganBuildingComponent;
struct FInputActionValue;
class UMorganInputDataConfig;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MORGAN_API AMorganPlayerCharacter : public AMorganCharacterBase
{
	GENERATED_BODY()

public:
	AMorganPlayerCharacter();

protected:
	virtual void OnDeath() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UMorganBuildingComponent> BuildingComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathAnimMontage;
};
