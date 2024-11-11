// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MorganIsTargetCloseDecorator.generated.h"

UCLASS()
class MORGAN_API UMorganIsTargetCloseDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMorganIsTargetCloseDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector TargetKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float MinDistance = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float BuildingAcceptanceRadius = 1000.0f;
};
