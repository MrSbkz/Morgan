// Copyrights P.K.

#include "Actors/CannonBuildingActor.h"
#include "Components/ArrowComponent.h"
#include "Weapon/MorganCannonball.h"

ACannonBuildingActor::ACannonBuildingActor()
{
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(GetRootComponent());
}

void ACannonBuildingActor::Attack()
{
	if (!GetWorld() || !IsActive) return;
	
	AMorganCannonball* Cannonball = GetWorld()->SpawnActorDeferred<AMorganCannonball>(CannonballClass, Arrow->GetComponentTransform());
	if(!Cannonball) return;
	
	Cannonball->SetOwner(this);
	Cannonball->SetShotDirection(Arrow->GetForwardVector());
	Cannonball->FinishSpawning(Arrow->GetComponentTransform());
}

void ACannonBuildingActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACannonBuildingActor::Attack, ReloadTime, true);
}
