// Copyrights P.K.

#include "Actors/BarrelBuildingActor.h"
#include "Kismet/GameplayStatics.h"

void ABarrelBuildingActor::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ABarrelBuildingActor::OnTakeDamage);
}

void ABarrelBuildingActor::OnTakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (!IsActive || !InstigatedBy->IsPlayerController()) return;

	FVector ExplosionLocation = GetActorLocation();
	ExplosionLocation.Z = +100.0f;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());

	// TODO: Check if damage applies to another barrel
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		ExplosionDamageAmount,
		ExplosionLocation,
		ExplosionRadius,
		UDamageType::StaticClass(),
		{},
		this,
		InstigatedBy,
		false);

	Destroy();
}
