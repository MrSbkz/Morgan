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

	void SetGoldAmount(const int32 EnemyLevel) { GoldAmount = GoldAmountPerLevel * EnemyLevel; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, Category="Pickups")
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, Category="Pickups")
	int32 GoldAmountPerLevel = 100;

	UPROPERTY(EditDefaultsOnly, Category="Pickups")
	float LifeTime = 10.0f;

private:
	int32 GoldAmount = 1000;
};
