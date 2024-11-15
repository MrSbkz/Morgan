// Copyrights P.K.

#include "AI/MorganAIController.h"
#include "Components/MorganAIPerceptionComponent.h"

AMorganAIController::AMorganAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UMorganAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AMorganAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTreeAsset);
}
