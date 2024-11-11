// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "MorganAIController.generated.h"

class UMorganAIPerceptionComponent;

UCLASS()
class MORGAN_API AMorganAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMorganAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UMorganAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector MainBuildingKey;

};
