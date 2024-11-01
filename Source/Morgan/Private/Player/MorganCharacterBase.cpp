// Copyrights P.K.

#include "Player/MorganCharacterBase.h"
#include "Components/MorganWeaponComponent.h"

AMorganCharacterBase::AMorganCharacterBase()
{

	WeaponComponent = CreateDefaultSubobject<UMorganWeaponComponent>("WeaponComponent");
}

void AMorganCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}
