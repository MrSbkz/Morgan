// Copyrights P.K.

#include "Weapon/MorganPistolWeapon.h"
#include "Animations/AnimUtils.h"
#include "Animations/MorganReloadFinishedAnimNotify.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

void AMorganPistolWeapon::Attack()
{
	if (IsAttackAnimInProgress || IsReloadAnimInProgress) return;
	MakeShot();
	--BulletsLeft;
	OnBulletsUpdated.Broadcast(BulletsLeft);
	UE_LOG(LogTemp, Warning, TEXT("Bullets left: %i"), BulletsLeft);
	Super::Attack();
}

void AMorganPistolWeapon::Reload()
{
	Super::Reload();

	if (BulletsLeft < BulletsAmount)
	{
		StartReloading();
	}
}

void AMorganPistolWeapon::BeginPlay()
{
	Super::BeginPlay();

	BulletsLeft = BulletsAmount;
	IsReloadAnimInProgress = false;
}

void AMorganPistolWeapon::InitAnimations()
{
	Super::InitAnimations();

	if (UMorganReloadFinishedAnimNotify* ReloadFinishedAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganReloadFinishedAnimNotify>(ReloadAnimation))
	{
		ReloadFinishedAnimNotify->OnNotify.AddUObject(this, &AMorganPistolWeapon::OnReloadAnimationFinished);
	}
}

void AMorganPistolWeapon::PostAttackAnimFinished()
{
	Super::PostAttackAnimFinished();
	if (BulletsLeft == 0)
	{
		StartReloading();
	}
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

void AMorganPistolWeapon::OnReloadAnimationFinished(USkeletalMeshComponent* MeshComp)
{
	if (!IsSameCharacter(MeshComp)) return;

	IsReloadAnimInProgress = false;
	BulletsLeft = BulletsAmount;
	OnBulletsUpdated.Broadcast(BulletsLeft);
	UE_LOG(LogTemp, Warning, TEXT("Finish reloading"));
}

void AMorganPistolWeapon::StartReloading()
{
	UE_LOG(LogTemp, Warning, TEXT("Start reloading"));
	IsReloadAnimInProgress = true;
	PlayAnimMontage(ReloadAnimation);
}
