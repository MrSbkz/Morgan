// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganMainBuilding.generated.h"

class UBoxComponent;
class UMorganHealthComponent;

UCLASS()
class MORGAN_API AMorganMainBuilding : public AActor
{
	GENERATED_BODY()

public:
	AMorganMainBuilding();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UMorganHealthComponent> HealthComponent;
};
