// Copyrights P.K.

#include "Components/MorganAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/MorganHealthComponent.h"
#include "Interfaces/EnemyInterface.h"
#include "Perception/AISense_Damage.h"
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

AActor* UMorganAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0)  return nullptr;

	const AAIController* Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const APawn* Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (AActor* PerceivedActor : PerceivedActors)
	{
		const UMorganHealthComponent* HealthComponent = PerceivedActor->FindComponentByClass<UMorganHealthComponent>();
		const bool IsEnemy = PerceivedActor->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass());
		if (HealthComponent && !HealthComponent->IsDead() && IsEnemy)
		{
			const float CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceivedActor;
			}
		}
	}

	return BestPawn;
}
