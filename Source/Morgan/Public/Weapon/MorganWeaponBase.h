// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganWeaponBase.generated.h"

UCLASS()
class MORGAN_API AMorganWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AMorganWeaponBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float WeaponDamage;
};
