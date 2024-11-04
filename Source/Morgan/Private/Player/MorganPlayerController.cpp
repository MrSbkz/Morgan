// Copyrights P.K.

#include "Player/MorganPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "Input/MorganInputDataConfig.h"

void AMorganPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (GetPawn())
	{
		if (const auto WeaponComponent = GetPawn()->FindComponentByClass<UMorganBuildingComponent>())
		{
			WeaponComponent->OnMenuOpened.AddUObject(this, &AMorganPlayerController::OnWidgetOpened);
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
		Input->BindAction(InputDataConfig->PistolReload, ETriggerEvent::Started, this,
		                  &AMorganPlayerController::Reload);
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

void AMorganPlayerController::OnWidgetOpened(const bool IsOpened)
{
	if(IsOpened)
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
