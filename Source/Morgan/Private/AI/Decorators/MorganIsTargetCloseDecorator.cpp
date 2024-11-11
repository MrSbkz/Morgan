// Copyrights P.K.

#include "AI/Decorators/MorganIsTargetCloseDecorator.h"
#include "AIController.h"
#include "Actors/MorganMainBuilding.h"
#include "BehaviorTree/BlackboardComponent.h"

UMorganIsTargetCloseDecorator::UMorganIsTargetCloseDecorator()
{
	NodeName = "Is Target Close";
}

bool UMorganIsTargetCloseDecorator::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;

	const AAIController* Controller = Cast<AAIController>(OwnerComp.GetOwner());
	if (!Controller) return false;

	const APawn* Pawn = Cast<APawn>(Controller->GetPawn());
	if (!Pawn) return false;

	const AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!Target) return false;

	const FVector PawnLocation = Pawn->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();

	const float Distance = (TargetLocation - PawnLocation).Size();

	if(Target->IsA<AMorganMainBuilding>())
	{
		return Distance <= MinDistance + BuildingAcceptanceRadius;
	}

	return Distance <= MinDistance;
}
