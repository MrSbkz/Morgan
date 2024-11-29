// Copyrights P.K.

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

	void SetLevel(const int32 InLevel);
	void SetHasLoot(const bool InHasLoot);

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath() override;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	float HealthWidgetLifeTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category="Loot")
	TSubclassOf<AMorganChestPickUp> LootClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnemyLevel")
	TMap<int32, TSoftObjectPtr<USkeletalMesh>> Meshes;

private:
	void OnHealthChanged(float HealthPercent);
	void OnWidgetLifeTimeFinished();
	void SpawnLoot() const;

	bool HasLoot = false;
	int32 Level = 1;

	FTimerHandle WidgetLifeTimeTimerHandle;
};
