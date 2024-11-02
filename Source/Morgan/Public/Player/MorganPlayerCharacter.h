// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Player/MorganCharacterBase.h"
#include "MorganPlayerCharacter.generated.h"

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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void OnDeath() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMorganInputDataConfig> InputDataConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
};
