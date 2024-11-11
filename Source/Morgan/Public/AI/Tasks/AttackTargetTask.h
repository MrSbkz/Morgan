// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackTargetTask.generated.h"

/**
 * 
 */
UCLASS()
class MORGAN_API UAttackTargetTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAttackTargetTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
