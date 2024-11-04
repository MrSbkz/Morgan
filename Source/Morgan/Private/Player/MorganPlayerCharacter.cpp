// Copyrights P.K.

#include "Player/MorganPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/MorganBuildingComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMorganPlayerCharacter::AMorganPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	BuildingComponent = CreateDefaultSubobject<UMorganBuildingComponent>("BuildingComponent");
}

void AMorganPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (DeathAnimMontage)
	{
		PlayAnimMontage(DeathAnimMontage);
	}
}
