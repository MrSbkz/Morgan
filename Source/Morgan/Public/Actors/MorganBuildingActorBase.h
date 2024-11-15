// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorganBuildingActorBase.generated.h"

class UBoxComponent;

UCLASS()
class MORGAN_API AMorganBuildingActorBase : public APawn
{
	GENERATED_BODY()

public:
	AMorganBuildingActorBase();

	bool CanBuild() const;
	void Activate();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UBoxComponent> Collision;

	bool IsActive = false;

private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	bool IsOnGround() const;

	bool IsCollisionOverlapped = false;
};
