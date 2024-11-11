// Copyrights P.K.

#include "AI/Tasks/AttackTargetTask.h"
#include "AIController.h"
#include "Components/MorganWeaponComponent.h"

UAttackTargetTask::UAttackTargetTask()
{
	NodeName = "Attack Target";
}

EBTNodeResult::Type UAttackTargetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	const APawn* Pawn = AIController->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	UMorganWeaponComponent* WeaponComponent = Pawn->FindComponentByClass<UMorganWeaponComponent>();
	if(!WeaponComponent) return EBTNodeResult::Failed;

	WeaponComponent->Attack();
	
	return EBTNodeResult::Succeeded;
}
