// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorganHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMorganHealthComponent();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(ClampMin="1.0", ClampMax="500.0"))
	float MaxHealth = 100.0f;

private:
	void SetHealth(float NewHealth);

	float Health = 100.0f;
};
