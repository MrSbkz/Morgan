// Copyrights P.K.

#include "Components/MorganHealthComponent.h"
#include "AI/Character/MorganKnightSkeletonCharacter.h"

void UMorganHealthComponent::SetHealthLevel(const int32 Level)
{
	const float HealthToAdd = InitialMaxHealth + IncreasedHealth * (Level - 1) - MaxHealth;
	
	MaxHealth += HealthToAdd;
	Health += HealthToAdd;
	SetHealth(Health);
	
	UE_LOG(LogTemp, Error, TEXT("Owner: %s, Level: %i, Health: %f"),
		*GetOwner()->GetClass()->GetName(),
		Level,
		Health);
}

void UMorganHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = InitialMaxHealth;
	SetHealth(InitialMaxHealth);

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
