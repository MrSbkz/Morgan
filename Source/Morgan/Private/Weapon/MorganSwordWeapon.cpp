// Copyrights P.K.

#include "Weapon/MorganSwordWeapon.h"
#include "Animations/AnimUtils.h"
#include "Animations/MorganSwordAttackDisableAnimNotify.h"
#include "Animations/MorganSwordAttackEnableAnimNotify.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

AMorganSwordWeapon::AMorganSwordWeapon()
{
	SwordCollision = CreateDefaultSubobject<UCapsuleComponent>("SwordCollision");
	SwordCollision->SetupAttachment(GetRootComponent());
}

void AMorganSwordWeapon::BeginPlay()
{
	Super::BeginPlay();

	SwordCollision->SetCollisionResponseToAllChannels(ECR_Ignore);

	FTimerHandle TimerHandle;
	const float RandomRate = FMath::RandRange(1.0f, 5.0f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMorganSwordWeapon::Attack, RandomRate, true);
}

void AMorganSwordWeapon::InitAnimations()
{
	Super::InitAnimations();

	if (UMorganSwordAttackEnableAnimNotify* SwordAttackEnableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackEnableAnimNotify>(AttackAnimation))
	{
		SwordAttackEnableAnimNotify->OnNotify.AddLambda([this](const USkeletalMeshComponent* MeshComp)
		{
			if (!IsSameCharacter(MeshComp)) return;

			SwordCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
		});
	}

	if (UMorganSwordAttackDisableAnimNotify* SwordAttackDisableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackDisableAnimNotify>(AttackAnimation))
	{
		SwordAttackDisableAnimNotify->OnNotify.AddLambda([this](const USkeletalMeshComponent* MeshComp)
		{
			if (!IsSameCharacter(MeshComp)) return;

			SwordCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
		});
	}
}

bool AMorganSwordWeapon::IsSameCharacter(const USkeletalMeshComponent* MeshComp) const
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	return Character && Character->GetMesh() == MeshComp;
}
