// Copyrights P.K.

#include "Components/MorganWeaponComponent.h"
#include "GameFramework/Character.h"
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
