// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MorganFindEnemyService.generated.h"

UCLASS()
class MORGAN_API UMorganFindEnemyService : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EnemyKey;
};
