// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MorganCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UMorganInputDataConfig;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MORGAN_API AMorganCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMorganCharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMorganInputDataConfig> InputDataConfig;

private:

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
