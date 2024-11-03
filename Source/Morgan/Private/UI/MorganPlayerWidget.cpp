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
