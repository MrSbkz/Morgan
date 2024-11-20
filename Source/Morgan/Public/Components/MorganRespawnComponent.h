// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorganRespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Respawn();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Respawn")
	int32 StartedRespawnTime = 3;
};
