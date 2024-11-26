// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganWeaponBase.h"
#include "MorganPistolWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBulletsUpdatedSignature, const int32);

class UNiagaraSystem;

UCLASS()
class MORGAN_API AMorganPistolWeapon : public AMorganWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	virtual void Reload() override;
	int32 GetBulletsAmount() const { return BulletsAmount; }

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	FOnBulletsUpdatedSignature OnBulletsUpdated;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> ReloadAnimation;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta=(ClampMin="0"))
	int32 BulletsAmount = 10;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	TObjectPtr<UParticleSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	FName MuzzleSocketName = "MuzzleSocket";

protected:
	virtual void BeginPlay() override;
	virtual void InitAnimations() override;
	virtual void PostAttackAnimFinished() override;

private:
	void MakeShot() const;
	void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(const FVector& TraceStart, const FVector& TraceEnd) const;
	void OnReloadAnimationFinished(USkeletalMeshComponent* MeshComp);
	void StartReloading();
	void SpawnMuzzleFX() const;

	int32 BulletsLeft;
	bool IsReloadAnimInProgress;
};
