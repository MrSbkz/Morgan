// Copyrights P.K.

#include "Player/MorganPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/MorganBuildingComponent.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganRespawnComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MorganPlayerState.h"
#include "UI/MorganHUD.h"

AMorganPlayerCharacter::AMorganPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	BuildingComponent = CreateDefaultSubobject<UMorganBuildingComponent>("BuildingComponent");
	RespawnComponent = CreateDefaultSubobject<UMorganRespawnComponent>("RespawnComponent");
}

void AMorganPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (const AMorganHUD* MorganHUD = Cast<AMorganHUD>(PlayerController->GetHUD()))
		{
			MorganHUD->BindToHealthComponent(HealthComponent);
			MorganHUD->BindToWeaponComponent(WeaponComponent);
		}
	}

	if (const AMorganPlayerState* MorganPlayerState = Cast<AMorganPlayerState>(GetPlayerState()))
	{
		WeaponComponent->SetWeaponLevel(MorganPlayerState->GetWeaponLevel());
		HealthComponent->SetHealthLevel(MorganPlayerState->GetHealthLevel());
	}
}

void AMorganPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
	}

	if (RespawnComponent)
	{
		RespawnComponent->Respawn();
	}

	if (BuildingComponent)
	{
		BuildingComponent->ClearBuildingData();
	}

	if (AMorganPlayerState* MorganPlayerState = Cast<AMorganPlayerState>(GetPlayerState()))
	{
		MorganPlayerState->IncreaseDeathsCount();
	}

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
