// Copyrights P.K.

#include "Player/MorganPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/MorganInputDataConfig.h"


AMorganPlayerCharacter::AMorganPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMorganPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputDataConfig, TEXT("InputDataConfig is null"));

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &AMorganPlayerCharacter::Move);
		Input->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &AMorganPlayerCharacter::Look);
		Input->BindAction(InputDataConfig->Attack, ETriggerEvent::Started, this, &AMorganPlayerCharacter::Attack);
		Input->BindAction(InputDataConfig->PistolReload, ETriggerEvent::Started, this, &AMorganPlayerCharacter::Reload);
	}
}

void AMorganPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
	}
}

void AMorganPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMorganPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMorganPlayerCharacter::Attack()
{
	WeaponComponent->Attack();
}

void AMorganPlayerCharacter::Reload()
{
	WeaponComponent->Reload();
}
