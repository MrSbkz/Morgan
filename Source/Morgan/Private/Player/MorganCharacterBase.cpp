// Copyrights P.K.

#include "Player/MorganCharacterBase.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"

AMorganCharacterBase::AMorganCharacterBase()
{
	WeaponComponent = CreateDefaultSubobject<UMorganWeaponComponent>("WeaponComponent");
	HealthComponent = CreateDefaultSubobject<UMorganHealthComponent>("HealthComponent");
}
