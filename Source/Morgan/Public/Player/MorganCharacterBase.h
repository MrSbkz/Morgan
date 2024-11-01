// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MorganCharacterBase.generated.h"

class UMorganWeaponComponent;

UCLASS()
class MORGAN_API AMorganCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMorganCharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UMorganWeaponComponent> WeaponComponent;
};
