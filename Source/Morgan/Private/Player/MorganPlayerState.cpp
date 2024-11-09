// Copyrights P.K.

#include "Player/MorganPlayerState.h"

void AMorganPlayerState::AddGold(const int32 Gold)
{
	GoldAmount += Gold;
	OnGoldAmountChanged.Broadcast(GoldAmount, Gold);
}
