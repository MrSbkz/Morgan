// Copyrights P.K.

#include "Components/MorganHealthComponent.h"

UMorganHealthComponent::UMorganHealthComponent()
{
}

void UMorganHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
}

void UMorganHealthComponent::SetHealth(const float NewHealth)
{
	Health = NewHealth;
}
