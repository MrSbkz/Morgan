// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganWeaponBase.h"
#include "MorganSwordWeapon.generated.h"

class UCapsuleComponent;

UCLASS()
class MORGAN_API AMorganSwordWeapon : public AMorganWeaponBase
{
	GENERATED_BODY()

public:
	AMorganSwordWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void InitAnimations() override;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UCapsuleComponent> SwordCollision;

private:
	bool IsSameCharacter(const USkeletalMeshComponent* MeshComp) const;
};
