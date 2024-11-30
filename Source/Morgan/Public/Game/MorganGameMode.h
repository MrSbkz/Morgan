// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "MorganGameMode.generated.h"

class AAIController;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWaveDataUpdatedSignature, int32);

UCLASS()
class MORGAN_API AMorganGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMorganGameMode();
	virtual void StartPlay() override;
	void RespawnRequest(const int32 RespawnTime);
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	virtual bool ClearPause() override;
	void EnemyDied();

	FOnGameStateChangedSignature OnGameStateChanged;
	FOnWaveDataUpdatedSignature OnNextWaveTimeUpdated;
	FOnWaveDataUpdatedSignature OnCurrentWaveUpdated;

	TMap<EBuildingItemType, FBuildingItemData> GetBuildingItems() { return BuildingItems; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Building")
	TMap<EBuildingItemType, FBuildingItemData> BuildingItems;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<ACharacter> EnemyCharacterClass;

	UPROPERTY(EditDefaultsOnly, Category="Wave")
	TArray<FEnemiesWave> EnemiesWaves;

	UPROPERTY(EditDefaultsOnly, Category="Wave")
	int32 NextWaveTime = 5;

private:
	void RespawnTimerUpdate();
	void RespawnPlayer(AController* Controller);
	void SpawnEnemies(FWaveEnemiesType EnemiesType);
	AActor* GetEnemyStart();
	static void SetEnemy(ACharacter* EnemyCharacter, const int32 EnemyLevel, const bool HasLoot);
	void StartWave();
	void NextWaveTimerUpdate();
	
	FTimerHandle RespawnTimerHandle;
	FTimerHandle NextWaveTimerHandle;
	int32 RespawnCountDown = 0;
	int32 NextWaveCountDown = 0;
	int32 CurrentWave = 1;

	UPROPERTY()
	TArray<AActor*> EnemyPlayerStarts;

	int32 EnemiesLeft = 0;
};
