// Copyrights P.K.

#include "UI/MorganPlayerWidget.h"
#include "Components/MorganHealthComponent.h"
#include "UI/MorganHealthBarWidget.h"

void UMorganPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UMorganHealthComponent* HealthComponent = Pawn->FindComponentByClass<UMorganHealthComponent>())
		{
			HealthComponent->OnHealthChanged.AddLambda([this](const float HealthPercent)
			{
				if (HealthBar)
				{
					HealthBar->SetHealth(HealthPercent);
				}
			});
		}
	}
}

void UMorganPlayerWidget::BindToHealthComponent(UMorganHealthComponent* HealthComponent) const
{
	if (!HealthComponent)
	{
		return;
	}

	HealthComponent->OnHealthChanged.Clear();

	HealthComponent->OnHealthChanged.AddLambda([this](const float HealthPercent)
	{
		if (HealthBar)
		{
			HealthBar->SetHealth(HealthPercent);
		}
	});
	HealthBar->SetHealth(1.0f);
}
