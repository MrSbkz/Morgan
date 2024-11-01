// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Player/MorganCharacterBase.h"
#include "MorganEnemyCharacter.generated.h"

UCLASS()
class MORGAN_API AMorganEnemyCharacter : public AMorganCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditAnywhere, Category="EnemyLevel", meta=(ClampMin="1", ClampMax="3"))
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnemyLevel")
	TMap<int32, TSoftObjectPtr<USkeletalMesh>> Meshes;
};
