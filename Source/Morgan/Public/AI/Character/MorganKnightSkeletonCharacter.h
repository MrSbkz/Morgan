// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Player/MorganCharacterBase.h"
#include "MorganKnightSkeletonCharacter.generated.h"

UCLASS()
class MORGAN_API AMorganKnightSkeletonCharacter : public AMorganCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="EnemyLevel", meta=(ClampMin="1", ClampMax="3"))
	int32 Level = 1;
};
