// Copyrights P.K.

#include "AI/Services/MorganFindTargetService.h"
#include "AIController.h"
#include "Actors/MorganMainBuilding.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/MorganAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"

void UMorganFindTargetService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent())
	{
		if (!MainBuildingActor)
		{
			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMorganMainBuilding::StaticClass(), Actors);
			if (Actors.Num() > 0)
			{
				MainBuildingActor = Actors[0];
			}
		}

		AActor* Target = nullptr;
		const AAIController* Controller = OwnerComp.GetAIOwner();
		if (const UMorganAIPerceptionComponent* PerceptionComponent =
			Controller->FindComponentByClass<UMorganAIPerceptionComponent>())
		{
			Target = PerceptionComponent->GetPlayer();
		}

		if (!Target)
		{
			Target = MainBuildingActor;
		}

		BlackBoard->SetValueAsObject(TargetKey.SelectedKeyName, Target);
	}


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
