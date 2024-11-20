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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MORGAN_API UMorganBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMorganBuildingComponent();
	void OpenCloseMenu();
	void StartBuilding(EBuildingItemType BuildingItemType);
	void ClearBuildingData();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category="Building")
	float TraceMaxDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> CompleteBuildingAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> BuildingMappingContext;

private:
	void PreviewBuildingItem();

	void GetTraceData(FVector& TraceStart, FVector& TraceEnd, FRotator& ViewRotation) const;
	void StartPreview(const FVector& TraceStart, FVector& TraceEnd, FRotator& ViewRotation);
	void CompleteBuilding();
	APlayerController* GetPlayerController() const;
	TMap<EBuildingItemType, FBuildingItemData> GetBuildingItems() const;

	bool IsMenuOpened = false;
	bool IsBuildingMode = false;
	FTimerHandle BuildingItemTimerHandle;
	int32 CurrentItemCost = 0;

	TSubclassOf<AMorganBuildingActorBase> CurrentBuildingActorClass;

	UPROPERTY()
	AMorganBuildingActorBase* CurrentBuildingActor;
};
