// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorganBuildingComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMenuOpenedSignature, const bool)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnMenuOpenedSignature OnMenuOpened;
};
