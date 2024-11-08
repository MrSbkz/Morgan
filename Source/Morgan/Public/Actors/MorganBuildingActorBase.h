// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganBuildingActorBase.generated.h"

UCLASS()
class MORGAN_API AMorganBuildingActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMorganBuildingActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
