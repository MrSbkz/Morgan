// Copyrights P.K.

#include "Components/MorganWeaponComponent.h"
#include "Animations/AnimUtils.h"
#include "Animations/MorganAttackFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/MorganWeaponBase.h"

void UMorganWeaponComponent::Attack()
{
	if (IsAttackAnimInProgress) return;

	PlayAnimMontage(AttackAnimation);
	IsAttackAnimInProgress = true;
}

void UMorganWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
	SpawnWeapon();
}

void UMorganWeaponComponent::InitAnimations()
{
	if (UMorganAttackFinishedAnimNotify* AttackFinishedAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganAttackFinishedAnimNotify>(AttackAnimation))
	{
		AttackFinishedAnimNotify->OnNotify.AddLambda([this](const USkeletalMeshComponent* MeshComp)
		{
			const ACharacter* Character = Cast<ACharacter>(GetOwner());
			if (!Character || Character->GetMesh() != MeshComp) return;

			IsAttackAnimInProgress = false;
		});
	}
}

void UMorganWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}

void UMorganWeaponComponent::SpawnWeapon() const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	AMorganWeaponBase* Weapon = GetWorld()->SpawnActor<AMorganWeaponBase>(WeaponClass);
	if (!Weapon) return;

	Weapon->SetOwner(Character);
	AttachWeaponToSocket(Weapon, Character->GetMesh());
}

void UMorganWeaponComponent::AttachWeaponToSocket(
	AMorganWeaponBase* Weapon,
	USceneComponent* SceneComponent) const
{
	if (!Weapon || !SceneComponent) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, WeaponEquipSocketName);
}
