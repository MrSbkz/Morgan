// Copyrights P.K.

#include "Actors/MorganMainBuilding.h"
#include "Components/MorganHealthComponent.h"

AMorganMainBuilding::AMorganMainBuilding()
{	
	HealthComponent = CreateDefaultSubobject<UMorganHealthComponent>("HealthComponent");
}
