// Copyrights P.K.

#include "UI/MorganMainBuildingHealthWidget.h"
#include "Actors/MorganMainBuilding.h"
#include "Components/MorganHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MorganHealthBarWidget.h"

void UMorganMainBuildingHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!GetWorld()) return;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMorganMainBuilding::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		if (UMorganHealthComponent* HealthComponent = Actors[0]->FindComponentByClass<UMorganHealthComponent>())
		{
			HealthComponent->OnHealthChanged.AddLambda([this](const float HealthPercent)
			{
				if (HealthBar)
				{
					HealthBar->SetHealth(HealthPercent);
				}
			});
			HealthBar->SetHealth(1.0f);
		}
	}
}
