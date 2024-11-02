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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMorganSwordWeapon::Attack, 5.0f, true);
}

void AMorganSwordWeapon::InitAnimations()
{
	Super::InitAnimations();

	if (UMorganSwordAttackEnableAnimNotify* SwordAttackEnableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackEnableAnimNotify>(AttackAnimation))
	{
		SwordAttackEnableAnimNotify->OnNotify.AddLambda([this](const USkeletalMeshComponent* MeshComp)
		{
			const ACharacter* Character = Cast<ACharacter>(GetOwner());
			if (!Character || Character->GetMesh() != MeshComp) return;

			SwordCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
		});
	}

	if (UMorganSwordAttackDisableAnimNotify* SwordAttackDisableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackDisableAnimNotify>(AttackAnimation))
	{
		SwordAttackDisableAnimNotify->OnNotify.AddLambda([this](const USkeletalMeshComponent* MeshComp)
		{
			const ACharacter* Character = Cast<ACharacter>(GetOwner());
			if (!Character || Character->GetMesh() != MeshComp) return;

			SwordCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
		});
	}
}
