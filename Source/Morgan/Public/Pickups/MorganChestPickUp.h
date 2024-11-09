// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganChestPickUp.generated.h"

class USphereComponent;

UCLASS()
class MORGAN_API AMorganChestPickUp : public AActor
{
	GENERATED_BODY()

public:
	AMorganChestPickUp();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, Category="Pickups")
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, Category="Pickups")
	int32 GoldAmount;
};
