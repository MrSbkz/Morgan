// Copyrights P.K.

#include "Player/MorganCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMorganCharacterBase::AMorganCharacterBase()
{
	WeaponComponent = CreateDefaultSubobject<UMorganWeaponComponent>("WeaponComponent");
	HealthComponent = CreateDefaultSubobject<UMorganHealthComponent>("HealthComponent");
}

void AMorganCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	HealthComponent->OnDeath.AddUObject(this, &AMorganCharacterBase::OnDeath);
}

void AMorganCharacterBase::OnDeath()
{
	SetLifeSpan(5.0f);
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}
