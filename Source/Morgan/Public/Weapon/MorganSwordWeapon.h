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

	UFUNCTION()
	void OnSwordBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void OnSwordAttackEnabled(USkeletalMeshComponent* MeshComp);
	void OnSwordAttackDisabled(USkeletalMeshComponent* MeshComp);
};
