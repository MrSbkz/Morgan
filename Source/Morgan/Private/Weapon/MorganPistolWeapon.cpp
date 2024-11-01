// Copyrights P.K.

#include "Weapon/MorganPistolWeapon.h"

#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

void AMorganPistolWeapon::Attack()
{
	Super::Attack();

	MakeShot();
}

void AMorganPistolWeapon::MakeShot() const
{
	FVector TraceStart, TraceEnd;
	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
}

void AMorganPistolWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FRotator ViewRotation;

	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	const APlayerController* PlayerController = Character->GetController<APlayerController>();
	if (!PlayerController) return;

	PlayerController->GetPlayerViewPoint(TraceStart, ViewRotation);

	TraceEnd = TraceStart + ViewRotation.Vector() * TraceMaxDistance;
}

void AMorganPistolWeapon::MakeHit(FHitResult& Hit, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	if (!Hit.bBlockingHit) return;

	AActor* DamageActor = Hit.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(
		DamageAmount,
		FDamageEvent(),
		GetController(),
		GetOwner()
	);
}
