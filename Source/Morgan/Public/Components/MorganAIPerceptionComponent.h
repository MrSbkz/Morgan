// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MorganAIPerceptionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetPlayer() const;
};
