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
	void SetWeaponLevel(int32 Level) const;
	AMorganWeaponBase* GetWeapon() const { return Weapon; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AMorganWeaponBase> WeaponClass;

private:
	void SpawnWeapon();
	void AttachWeaponToSocket(USceneComponent* SceneComponent) const;

	UPROPERTY()
	AMorganWeaponBase* Weapon;
};
