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
	virtual void InitAnimations();
	bool IsSameCharacter(const USkeletalMeshComponent* MeshComp) const;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float DamageAmount;

	bool IsAttackAnimInProgress;

private:
	void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	void OnAttackAnimationFinished(USkeletalMeshComponent* MeshComp);
};
