// Copyrights P.K.

#include "Components/MorganBuildingComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/MorganBuildingActorBase.h"
#include "UI/MorganHUD.h"
#include "Engine/World.h"
#include "Game/MorganGameMode.h"
#include "Player/MorganPlayerState.h"

UMorganBuildingComponent::UMorganBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMorganBuildingComponent::OpenCloseMenu()
{
	if (!GetOwner()) return;

	APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	const AMorganHUD* GameHUD = Cast<AMorganHUD>(PlayerController->GetHUD());
	if (!GameHUD) return;

	if (IsMenuOpened)
	{
		GameHUD->OpenClosedBuildingMenu(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		GameHUD->OpenClosedBuildingMenu(true);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
		if (CurrentBuildingActor)
		{
			CurrentBuildingActor->Destroy();
			CurrentBuildingActor = nullptr;
		}
		IsBuildingMode = false;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(BuildingMappingContext);
		}
	}

	IsMenuOpened = !IsMenuOpened;
}

void UMorganBuildingComponent::StartBuilding(const EBuildingItemType BuildingItemType)
{
	if (!GetWorld()) return;

	OpenCloseMenu();

	const APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(BuildingMappingContext, 1);
	}

	TMap<EBuildingItemType, FBuildingItemData> BuildingItems = GetBuildingItems();
	if (!BuildingItems.Contains(BuildingItemType)) return;

	CurrentBuildingActorClass = BuildingItems[BuildingItemType].BuildingItemClass;
	CurrentItemCost = BuildingItems[BuildingItemType].ItemCost;

	IsBuildingMode = true;
}

void UMorganBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		Input->BindAction(CompleteBuildingAction, ETriggerEvent::Triggered, this,
		                  &UMorganBuildingComponent::CompleteBuilding);
	}
}

void UMorganBuildingComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PreviewBuildingItem();
}

void UMorganBuildingComponent::PreviewBuildingItem()
{
	if (!IsBuildingMode) return;

	FVector TraceStart, TraceEnd;
	FRotator ViewRotation;
	GetTraceData(TraceStart, TraceEnd, ViewRotation);
	StartPreview(TraceStart, TraceEnd, ViewRotation);
}

void UMorganBuildingComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd, FRotator& ViewRotation) const
{
	const APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	PlayerController->GetPlayerViewPoint(TraceStart, ViewRotation);

	TraceEnd = TraceStart + ViewRotation.Vector() * TraceMaxDistance;
}

void UMorganBuildingComponent::StartPreview(const FVector& TraceStart, FVector& TraceEnd, FRotator& ViewRotation)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredActor(CurrentBuildingActor);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	if (Hit.bBlockingHit)
	{
		TraceEnd = Hit.ImpactPoint;
	}

	FTransform Transform;
	FRotator Rotation;
	Rotation.Yaw += ViewRotation.Yaw + 180.0f;
	Transform.SetRotation(Rotation.Quaternion());
	Transform.SetLocation(TraceEnd);
	if (CurrentBuildingActor)
	{
		CurrentBuildingActor->SetActorTransform(Transform);
	}
	else
	{
		CurrentBuildingActor = GetWorld()->SpawnActor<AMorganBuildingActorBase>(CurrentBuildingActorClass, Transform);
	}
}

void UMorganBuildingComponent::CompleteBuilding()
{
	if (!CurrentBuildingActor->CanBuild()) return;

	const APlayerController* PlayerController = GetPlayerController();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(BuildingMappingContext);
	}
	CurrentBuildingActor->Activate();

	if (AMorganPlayerState* PlayerState = PlayerController->GetPlayerState<AMorganPlayerState>())
	{
		PlayerState->AddGold(-CurrentItemCost);
	}

	IsBuildingMode = false;
	CurrentBuildingActor = nullptr;
}

APlayerController* UMorganBuildingComponent::GetPlayerController() const
{
	const APawn* Character = Cast<APawn>(GetOwner());
	if (!Character) return nullptr;

	return Character->GetController<APlayerController>();
}

TMap<EBuildingItemType, FBuildingItemData> UMorganBuildingComponent::GetBuildingItems() const
{
	AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return TMap<EBuildingItemType, FBuildingItemData>();

	return GameMode->GetBuildingItems();
}
