// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorganWeaponComponent.generated.h"

class AMorganWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Attack() const;
	void Reload() const;
	void DestroyWeapon() const;
	void SetWeaponLevel(int32 Level);
	float GetWeaponDamageAmount() const;
	int32 GetWeaponImprovementCost() const;
	AMorganWeaponBase* GetWeapon() const { return Weapon; }
	void SpawnWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AMorganWeaponBase> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	int32 ImprovementCostByLevel = 100;

private:
	void AttachWeaponToSocket(USceneComponent* SceneComponent) const;

	UPROPERTY()
	AMorganWeaponBase* Weapon;
};
