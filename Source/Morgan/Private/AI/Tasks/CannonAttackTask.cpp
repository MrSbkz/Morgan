// Copyrights P.K.

#include "AI/Tasks/CannonAttackTask.h"
#include "AIController.h"
#include "Actors/CannonBuildingActor.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCannonAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ACannonBuildingActor* Cannon = Cast<ACannonBuildingActor>(AIController->GetPawn());
	if (!Cannon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!BlackBoard) return EBTNodeResult::Failed;

	if (BlackBoard->GetValueAsObject(EnemyKey.SelectedKeyName))
	{
		Cannon->Attack();
	}

	return EBTNodeResult::Succeeded;
}
