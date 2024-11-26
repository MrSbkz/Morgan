// Copyrights P.K.

#include "Components/MorganWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Player/MorganPlayerState.h"
#include "Weapon/MorganWeaponBase.h"

void UMorganWeaponComponent::Attack() const
{
	if (!Weapon) return;

	Weapon->Attack();
}

void UMorganWeaponComponent::Reload() const
{
	Weapon->Reload();
}

void UMorganWeaponComponent::DestroyWeapon() const
{
	if (Weapon)
	{
		Weapon->Destroy();
	}
}

void UMorganWeaponComponent::SetWeaponLevel(const int32 Level)
{
	if (Weapon)
	{
		Weapon->SetLevel(Level);
	}
}

float UMorganWeaponComponent::GetWeaponDamageAmount() const
{
	if (Weapon)
	{
		return Weapon->GetDamageAmount();
	}

	return 30.0f;
}

int32 UMorganWeaponComponent::GetWeaponImprovementCost() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if(!Pawn) return 0;

	const AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(Pawn->GetPlayerState());
	if(!PlayerState) return 0;

	return PlayerState->GetWeaponLevel() * ImprovementCostByLevel;
}

void UMorganWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UMorganWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	Weapon = GetWorld()->SpawnActor<AMorganWeaponBase>(WeaponClass);
	if (!Weapon) return;

	Weapon->SetOwner(Character);
	AttachWeaponToSocket(Character->GetMesh());
}

void UMorganWeaponComponent::AttachWeaponToSocket(USceneComponent* SceneComponent) const
{
	if (!SceneComponent) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, WeaponEquipSocketName);
}
