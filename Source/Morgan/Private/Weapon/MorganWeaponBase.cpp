// Copyrights P.K.

#include "Weapon/MorganWeaponBase.h"

#include "Animations/AnimUtils.h"
#include "Animations/MorganAttackFinishedAnimNotify.h"
#include "GameFramework/Character.h"

AMorganWeaponBase::AMorganWeaponBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void AMorganWeaponBase::Attack()
{
	if (IsAttackAnimInProgress) return;

	PlayAnimMontage(AttackAnimation);
	IsAttackAnimInProgress = true;
}

void AMorganWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
}

AController* AMorganWeaponBase::GetController() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void AMorganWeaponBase::InitAnimations()
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

void AMorganWeaponBase::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}
