// Copyrights P.K.

#include "Components/MorganHealthComponent.h"
#include "AI/Character/MorganKnightSkeletonCharacter.h"
#include "Player/MorganPlayerState.h"

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

int32 UMorganHealthComponent::GetHealthImprovementCost() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if(!Pawn) return 0;

	const AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(Pawn->GetPlayerState());
	if(!PlayerState) return 0;

	return PlayerState->GetHealthLevel() * ImprovementCostByLevel;
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
