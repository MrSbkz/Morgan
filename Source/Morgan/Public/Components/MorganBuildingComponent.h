// Copyrights P.K.

#pragma once

#include "CoreMinimal.h"
#include "MorganCoreTypes.h"
#include "Components/ActorComponent.h"
#include "MorganBuildingComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class AMorganBuildingActorBase;
class UInputMappingContext;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMenuOpenedSignature, const bool)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMorganBuildingComponent();
	void OpenCloseMenu();
	void StartBuilding(EBuildingItemType BuildingItemType);

	FOnMenuOpenedSignature OnMenuOpened;

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category="Building")
	float TraceMaxDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* CompleteBuildingAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> BuildingMappingContext;

private:
	void PreviewBuildingItem();

	void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void StartPreview(const FVector& TraceStart, FVector& TraceEnd);
	void CompleteBuilding();
	APlayerController* GetPlayerController() const;
	

	bool IsMenuOpened = false;
	bool IsBuildingMode = false;
	FTimerHandle BuildingItemTimerHandle;

	TSubclassOf<AMorganBuildingActorBase> CurrentBuildingActorClass;

	UPROPERTY()
	TObjectPtr<AMorganBuildingActorBase> CurrentBuildingActor;
};
