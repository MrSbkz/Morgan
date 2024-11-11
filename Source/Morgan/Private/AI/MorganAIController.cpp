// Copyrights P.K.

#include "AI/MorganAIController.h"
#include "AI/Character/MorganKnightSkeletonCharacter.h"
#include "Components/MorganAIPerceptionComponent.h"

AMorganAIController::AMorganAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UMorganAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AMorganAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto SkeletonCharacter = Cast<AMorganKnightSkeletonCharacter>(InPawn))
	{
		RunBehaviorTree(SkeletonCharacter->BehaviorTreeAsset);
	}
}
