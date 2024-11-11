// Copyrights P.K.

#include "Components/MorganAIPerceptionComponent.h"
#include "Components/MorganHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/MorganPlayerCharacter.h"

AActor* UMorganAIPerceptionComponent::GetPlayer() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0) return nullptr;
	
	for (const auto PerceivedActor : PerceivedActors)
	{
		const UMorganHealthComponent* HealthComponent = PerceivedActor->FindComponentByClass<UMorganHealthComponent>();
		if (PerceivedActor->IsA<AMorganPlayerCharacter>() && HealthComponent && !HealthComponent->IsDead())
		{
			return PerceivedActor;
		}
	}

	return nullptr;
}
