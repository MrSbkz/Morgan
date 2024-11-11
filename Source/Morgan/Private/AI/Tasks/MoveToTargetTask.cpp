// Copyrights P.K.

#include "AI/Tasks/MoveToTargetTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMoveToTargetTask::UMoveToTargetTask()
{
	NodeName = "Move To Target";
}

EBTNodeResult::Type UMoveToTargetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (AActor* TargetBuilding = Cast<AActor>(BlackboardComp->GetValueAsObject(MainBuildingKey.SelectedKeyName)))
	{
		AIController->MoveToActor(TargetBuilding, 0.0f);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
