// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "MorganGameMode.generated.h"

class AAIController;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState);

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

	FOnGameStateChangedSignature OnGameStateChanged;

	TMap<EBuildingItemType, FBuildingItemData> GetBuildingItems() { return BuildingItems; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Building")
	TMap<EBuildingItemType, FBuildingItemData> BuildingItems;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<ACharacter> EnemyCharacterClass;

private:
	void RespawnTimerUpdate();
	void RespawnPlayer(AController* Controller);
	void SpawnEnemies();
	AActor* GetEnemyStart();
	static void SetEnemy(ACharacter* EnemyCharacter, const int32 EnemyLevel, const bool HasLoot);
	
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	UPROPERTY()
	TArray<AActor*> EnemyPlayerStarts;
};
