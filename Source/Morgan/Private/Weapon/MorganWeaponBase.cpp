// Copyrights P.K.

#include "Weapon/MorganWeaponBase.h"

AMorganWeaponBase::AMorganWeaponBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}
