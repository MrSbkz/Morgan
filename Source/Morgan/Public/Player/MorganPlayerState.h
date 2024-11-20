// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MorganPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGoldAmountChagedSignature, const int32, const int32);

UCLASS()
class MORGAN_API AMorganPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetGoldAmount() const { return GoldAmount; }
	void AddGold(const int32 Gold);

	int32 GetDeathsCount() const { return DeathsCount; }
	void IncreaseDeathsCount() { ++DeathsCount; }

	FOnGoldAmountChagedSignature OnGoldAmountChanged;

private:
	int32 GoldAmount = 0;
	int32 DeathsCount = 0;
};
