// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganCannonball.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MORGAN_API AMorganCannonball : public AActor
{
	GENERATED_BODY()

public:
	AMorganCannonball();
	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float DamageRadius = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float DamageAmount = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	bool DoFullDamage = true;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> ExplosionFX;

private:
	UFUNCTION()
	void OnProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	FVector ShotDirection;
};
