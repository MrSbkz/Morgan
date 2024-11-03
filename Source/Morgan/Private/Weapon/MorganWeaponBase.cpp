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
		AttackFinishedAnimNotify->OnNotify.AddUObject(this, &AMorganWeaponBase::OnAttackAnimationFinished);
	}
}

bool AMorganWeaponBase::IsSameCharacter(const USkeletalMeshComponent* MeshComp) const
{
	const ACharacter* Character = Cast<ACharacter>(Owner);
	return Character && Character->GetMesh() == MeshComp;
}

void AMorganWeaponBase::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}

void AMorganWeaponBase::OnAttackAnimationFinished(USkeletalMeshComponent* MeshComp)
{
	if (!IsSameCharacter(MeshComp)) return;

	IsAttackAnimInProgress = false;
}
