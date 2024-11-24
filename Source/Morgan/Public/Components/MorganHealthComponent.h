// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MorganHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	bool IsDead() const { return Health <= 0.0f; }
	void SetHealthLevel(const int32 Level);

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(ClampMin="1.0", ClampMax="1000.0"))
	float InitialMaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(ClampMin="1.0", ClampMax="100.0"))
	float IncreasedHealth = 50.0f;

private:
	void SetHealth(float NewHealth);
	float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION()
	void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);

	float Health = 100.0f;
	float MaxHealth;
};
