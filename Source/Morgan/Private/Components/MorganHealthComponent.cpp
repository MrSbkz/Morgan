// Copyrights P.K.

#include "Components/MorganHealthComponent.h"

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
	SetHealth(Health - Damage);
}
