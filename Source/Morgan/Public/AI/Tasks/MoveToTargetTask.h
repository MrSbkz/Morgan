// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToTargetTask.generated.h"

UCLASS()
class MORGAN_API UMoveToTargetTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMoveToTargetTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector MainBuildingKey;

};
