// Copyrights P.K.

#include "Actors/CannonBuildingActor.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/ArrowComponent.h"
#include "Weapon/MorganCannonball.h"

ACannonBuildingActor::ACannonBuildingActor()
{
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Mesh);

	bUseControllerRotationYaw = true;
}

void ACannonBuildingActor::Attack()
{
	if (!GetWorld() || !IsActive || !IsReadyToAttack) return;
	
	AMorganCannonball* Cannonball = GetWorld()->SpawnActorDeferred<AMorganCannonball>(CannonballClass, Arrow->GetComponentTransform());
	if(!Cannonball) return;
	
	Cannonball->SetOwner(this);
	Cannonball->SetShotDirection(Arrow->GetForwardVector());
	Cannonball->FinishSpawning(Arrow->GetComponentTransform());
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		MuzzleFX,
		Mesh,
		MuzzleSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true);

	IsReadyToAttack = false;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACannonBuildingActor::SetReadyToAttack, ReloadTime, false);
}

void ACannonBuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACannonBuildingActor::SetReadyToAttack()
{
	IsReadyToAttack = true;
}
