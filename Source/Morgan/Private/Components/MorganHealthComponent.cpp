// Copyrights P.K.

#include "Components/MorganHealthComponent.h"

void UMorganHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
}

void UMorganHealthComponent::SetHealth(const float NewHealth)
{
	Health = NewHealth;
}
