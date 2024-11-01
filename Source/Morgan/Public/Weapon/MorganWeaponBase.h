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
	virtual void Attack();

protected:
	virtual void BeginPlay() override;
	AController* GetController() const;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float DamageAmount;

private:
	void InitAnimations();
	void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	bool IsAttackAnimInProgress;
};
