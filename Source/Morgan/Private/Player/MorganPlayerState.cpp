// Copyrights P.K.

#include "Player/MorganPlayerState.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"

void AMorganPlayerState::AddGold(const int32 Gold)
{
	GoldAmount += Gold;
	OnGoldAmountChanged.Broadcast(GoldAmount, Gold);
}

void AMorganPlayerState::IncreaseHealthLevel()
{
	if(!GetPawn()) return;
	
	if(UMorganHealthComponent* HealthComponent = GetPawn()->FindComponentByClass<UMorganHealthComponent>())
	{
		++HealthLevel;
		HealthComponent->SetHealthLevel(HealthLevel);
	}
}

void AMorganPlayerState::IncreaseWeaponLevel()
{
	if(!GetPawn()) return;
	
	if(const UMorganWeaponComponent* WeaponComponent = GetPawn()->FindComponentByClass<UMorganWeaponComponent>())
	{
		++WeaponLevel;
		WeaponComponent->SetWeaponLevel(WeaponLevel);
	}
}
