// Copyrights P.K.

#include "Player/MorganPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "Game/MorganGameMode.h"
#include "Input/MorganInputDataConfig.h"
#include "Player/MorganPlayerState.h"
#include "UI/MorganHUD.h"

void AMorganPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (GetWorld() && GetWorld()->GetAuthGameMode())
	{
		if (AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnGameStateChanged.AddUObject(this, &AMorganPlayerController::OnGameStateChanged);
		}
	}
}

void AMorganPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	checkf(InputDataConfig, TEXT("InputDataConfig is null"));

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &AMorganPlayerController::Move);
		Input->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &AMorganPlayerController::Look);
		Input->BindAction(InputDataConfig->Attack, ETriggerEvent::Started, this, &AMorganPlayerController::Attack);
		Input->BindAction(
			InputDataConfig->PistolReload,
			ETriggerEvent::Started,
			this,
			&AMorganPlayerController::Reload
		);
		Input->BindAction(
			InputDataConfig->OpenBuildingMenu,
			ETriggerEvent::Started,
			this,
			&AMorganPlayerController::OpenBuildingMenu
		);
		Input->BindAction(InputDataConfig->Pause, ETriggerEvent::Started, this, &AMorganPlayerController::SetPause);
		Input->BindAction(InputDataConfig->OpenImprovementsMenu, ETriggerEvent::Started, this, &AMorganPlayerController::OpenImprovementsMenu);
	}
}

void AMorganPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const AMorganHUD* MorganHUD = Cast<AMorganHUD>(GetHUD()))
	{
		UMorganWeaponComponent* WeaponComponent = InPawn->FindComponentByClass<UMorganWeaponComponent>();
		UMorganHealthComponent* HealthComponent = InPawn->FindComponentByClass<UMorganHealthComponent>();
		if (const AMorganPlayerState* MorganPlayerState = Cast<AMorganPlayerState>(PlayerState))
		{
			if (WeaponComponent)
			{
				MorganHUD->BindToWeaponComponent(WeaponComponent);
				WeaponComponent->SetWeaponLevel(MorganPlayerState->GetWeaponLevel());
			}

			if (HealthComponent)
			{
				MorganHUD->BindToHealthComponent(HealthComponent);
				HealthComponent->SetHealthLevel(MorganPlayerState->GetHealthLevel());
			}
		}
	}
}

void AMorganPlayerController::OnGameStateChanged(EGameState GameState)
{
	if (GameState == EGameState::Pause)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void AMorganPlayerController::Move(const FInputActionValue& Value)
{
	if (!GetPawn()) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AMorganPlayerController::Look(const FInputActionValue& Value)
{
	if (!GetPawn()) return;

	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	GetPawn()->AddControllerYawInput(-LookAxisVector.X);
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
}

void AMorganPlayerController::Attack()
{
	if (!GetPawn()) return;

	if (const auto WeaponComponent = GetPawn()->FindComponentByClass<UMorganWeaponComponent>())
	{
		WeaponComponent->Attack();
	}
}

void AMorganPlayerController::Reload()
{
	if (!GetPawn()) return;

	if (const auto WeaponComponent = GetPawn()->FindComponentByClass<UMorganWeaponComponent>())
	{
		WeaponComponent->Reload();
	}
}

void AMorganPlayerController::OpenBuildingMenu()
{
	if (!GetPawn()) return;

	if (const auto BuildingComponent = GetPawn()->FindComponentByClass<UMorganBuildingComponent>())
	{
		BuildingComponent->OpenCloseMenu();
	}
}

void AMorganPlayerController::SetPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AMorganPlayerController::OpenImprovementsMenu()
{
	AMorganHUD* MorganHUD = Cast<AMorganHUD>(GetHUD());
	if(!MorganHUD) return;

	MorganHUD->OpenImprovementsMenu();
}
