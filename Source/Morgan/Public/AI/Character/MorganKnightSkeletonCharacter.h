﻿// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/EnemyInterface.h"
#include "Player/MorganCharacterBase.h"
#include "MorganKnightSkeletonCharacter.generated.h"

class UBehaviorTree;
class AMorganChestPickUp;
class UWidgetComponent;

UCLASS()
class MORGAN_API AMorganKnightSkeletonCharacter : public AMorganCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AMorganKnightSkeletonCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath() override;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category="EnemyLevel", meta=(ClampMin="1", ClampMax="3"))
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	float HealthWidgetLifeTime = 3.0f;

	UPROPERTY(EditAnywhere, Category="Loot")
	bool HasLoot = false;

	UPROPERTY(EditDefaultsOnly, Category="Loot")
	TSubclassOf<AMorganChestPickUp> LootClass;

private:
	void OnHealthChanged(float HealthPercent);
	void OnWidgetLifeTimeFinished();
	void SpawnLoot() const;

	FTimerHandle WidgetLifeTimeTimerHandle;
};
