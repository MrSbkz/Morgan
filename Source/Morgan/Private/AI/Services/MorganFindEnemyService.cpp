// Copyrights P.K.

#include "AI/Services/MorganFindEnemyService.h"
#include "AIController.h"
#include "Actors/CannonBuildingActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/MorganAIPerceptionComponent.h"

void UMorganFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent())
	{
		AAIController* Controller = OwnerComp.GetAIOwner();
		const ACannonBuildingActor* Cannon = Cast<ACannonBuildingActor>(Controller->GetPawn());
		if (Cannon->IsActorActive())
		{
			AActor* Enemy = nullptr;
			if (const UMorganAIPerceptionComponent* PerceptionComponent =
				Controller->FindComponentByClass<UMorganAIPerceptionComponent>())
			{
				Enemy = PerceptionComponent->GetClosestEnemy();
			}

			Controller->SetFocus(Enemy);
			BlackBoard->SetValueAsObject(EnemyKey.SelectedKeyName, Enemy);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
