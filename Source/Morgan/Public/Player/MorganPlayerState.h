// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MorganPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldAmountChagedSignature, int32)


UCLASS()
class MORGAN_API AMorganPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetGoldAmount() const { return GoldAmount; }
	void AddGold(const int32 Gold);

	FOnGoldAmountChagedSignature OnGoldAmountChanged;

private:
	int32 GoldAmount = 0;
};
