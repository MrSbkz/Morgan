// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganBuildingActorBase.h"
#include "CannonBuildingActor.generated.h"

class UNiagaraSystem;
class UArrowComponent;
class AMorganCannonball;

UCLASS()
class MORGAN_API ACannonBuildingActor : public AMorganBuildingActorBase
{
	GENERATED_BODY()

public:
	ACannonBuildingActor();
	void Attack();
	bool IsActorActive() const { return IsActive; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Compoennts")
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AMorganCannonball> CannonballClass;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY(EditDefaultsOnly, Category="VFX")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float ReloadTime = 5.0f;

private:
	void SetReadyToAttack();

	bool IsReadyToAttack = true;
};
