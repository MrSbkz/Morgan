// Copyrights P.K.

#include "Components/MorganHealthComponent.h"
#include "AI/Character/MorganKnightSkeletonCharacter.h"

void UMorganHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UMorganHealthComponent::OnTakeDamage);
	}
}

void UMorganHealthComponent::SetHealth(const float NewHealth)
{
	Health = NewHealth;

	OnHealthChanged.Broadcast(GetHealthPercent());

	if (Health <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

void UMorganHealthComponent::OnTakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (GetOwner()->IsA<AMorganKnightSkeletonCharacter>() == DamageCauser->IsA<AMorganKnightSkeletonCharacter>()) return;

	SetHealth(Health - Damage);
}
