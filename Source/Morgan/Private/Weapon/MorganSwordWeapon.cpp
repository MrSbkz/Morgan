// Copyrights P.K.

#include "Weapon/MorganSwordWeapon.h"
#include "Animations/AnimUtils.h"
#include "Animations/MorganSwordAttackDisableAnimNotify.h"
#include "Animations/MorganSwordAttackEnableAnimNotify.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

AMorganSwordWeapon::AMorganSwordWeapon()
{
	SwordCollision = CreateDefaultSubobject<UCapsuleComponent>("SwordCollision");
	SwordCollision->SetupAttachment(GetRootComponent());
}

void AMorganSwordWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (SwordCollision)
	{
		SwordCollision->OnComponentBeginOverlap.AddDynamic(this, &AMorganSwordWeapon::OnSwordBeginOverlap);
		SwordCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void AMorganSwordWeapon::InitAnimations()
{
	Super::InitAnimations();

	if (UMorganSwordAttackEnableAnimNotify* SwordAttackEnableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackEnableAnimNotify>(AttackAnimation))
	{
		SwordAttackEnableAnimNotify->OnNotify.AddUObject(this, &AMorganSwordWeapon::OnSwordAttackEnabled);
	}

	if (UMorganSwordAttackDisableAnimNotify* SwordAttackDisableAnimNotify =
		AnimUtils::FindAnimNotifyByClass<UMorganSwordAttackDisableAnimNotify>(AttackAnimation))
	{
		SwordAttackDisableAnimNotify->OnNotify.AddUObject(this, &AMorganSwordWeapon::OnSwordAttackDisabled);
	}
}

void AMorganSwordWeapon::OnSwordBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		OtherActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), GetOwner());
	}
}

void AMorganSwordWeapon::OnSwordAttackEnabled(USkeletalMeshComponent* MeshComp)
{
	if (!IsSameCharacter(MeshComp)) return;

	SwordCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	SwordCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMorganSwordWeapon::OnSwordAttackDisabled(USkeletalMeshComponent* MeshComp)
{
	if (!IsSameCharacter(MeshComp)) return;

	SwordCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SwordCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
