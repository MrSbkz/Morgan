// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Actors/MorganBuildingActorBase.h"
#include "BarrelBuildingActor.generated.h"

UCLASS()
class MORGAN_API ABarrelBuildingActor : public AMorganBuildingActorBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="FX")
	TObjectPtr<UParticleSystem> Explosion;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float ExplosionDamageAmount = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float ExplosionRadius = 300.0f;

private:
	UFUNCTION()
	void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);

	bool IsDamageTaken = false;
};
