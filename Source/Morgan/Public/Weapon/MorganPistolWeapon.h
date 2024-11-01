// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganWeaponBase.h"
#include "MorganPistolWeapon.generated.h"

UCLASS()
class MORGAN_API AMorganPistolWeapon : public AMorganWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Attack() override;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

private:
	void MakeShot() const;
	void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& Hit, const FVector& TraceStart, const FVector& TraceEnd) const;
};
