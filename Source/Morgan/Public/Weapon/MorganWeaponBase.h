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
	virtual void SetLevel(int32 Level);

	virtual void Reload()
	{
	};

protected:
	virtual void BeginPlay() override;
	virtual void InitAnimations();
	virtual void PlayAnimMontage(UAnimMontage* AnimMontage) const;

	virtual void PostAttackAnimFinished()
	{
	};

	AController* GetController() const;
	bool IsSameCharacter(const USkeletalMeshComponent* MeshComp) const;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float InitialDamageAmount = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float IncreasedDamageAmount = 20.0f;

	bool IsAttackAnimInProgress;
	float DamageAmount;

private:
	void OnAttackAnimationFinished(USkeletalMeshComponent* MeshComp);

};
