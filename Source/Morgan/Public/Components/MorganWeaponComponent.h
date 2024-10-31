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
	void Attack();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AMorganWeaponBase> WeaponClass;

private:
	void InitAnimations();
	void PlayAnimMontage(UAnimMontage* AnimMontage) const;	
	void SpawnWeapon() const;	
	void AttachWeaponToSocket(AMorganWeaponBase* Weapon, USceneComponent* SceneComponent) const;

	bool IsAttackAnimInProgress;
};
