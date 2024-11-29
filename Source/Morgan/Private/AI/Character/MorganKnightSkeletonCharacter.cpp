// Copyrights P.K.

#include "AI/Character/MorganKnightSkeletonCharacter.h"
#include "Components/MorganHealthComponent.h"
#include "Components/MorganWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pickups/MorganChestPickUp.h"
#include "UI/MorganHealthBarWidget.h"

AMorganKnightSkeletonCharacter::AMorganKnightSkeletonCharacter()
{
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AMorganKnightSkeletonCharacter::SetLevel(const int32 InLevel)
{
	checkf(Meshes.Num() > 0, TEXT("Meshes map is empty"));

	Level = InLevel;
	
	GetMesh()->SetSkeletalMesh(Meshes.Contains(Level) ? Meshes[Level].LoadSynchronous() : nullptr);

	WeaponComponent->SpawnWeapon();

	WeaponComponent->SetWeaponLevel(Level);
	HealthComponent->SetHealthLevel(Level);
}

void AMorganKnightSkeletonCharacter::SetHasLoot(const bool InHasLoot)
{
	HasLoot = InHasLoot;
}

void AMorganKnightSkeletonCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthWidgetComponent->SetVisibility(false);
	HealthComponent->OnHealthChanged.AddUObject(this, &AMorganKnightSkeletonCharacter::OnHealthChanged);
}

void AMorganKnightSkeletonCharacter::OnDeath()
{
	Super::OnDeath();

	GetMesh()->SetSimulatePhysics(true);
	OnWidgetLifeTimeFinished();
	SpawnLoot();
}

void AMorganKnightSkeletonCharacter::OnHealthChanged(const float HealthPercent)
{
	const UMorganHealthBarWidget* HealthBarWidget = Cast<UMorganHealthBarWidget>(
		HealthWidgetComponent->GetWidget()
	);

	HealthBarWidget->SetHealth(HealthPercent);

	HealthWidgetComponent->SetVisibility(true);

	GetWorldTimerManager().ClearTimer(WidgetLifeTimeTimerHandle);

	GetWorldTimerManager().SetTimer(
		WidgetLifeTimeTimerHandle,
		this,
		&AMorganKnightSkeletonCharacter::OnWidgetLifeTimeFinished,
		HealthWidgetLifeTime,
		false
	);
}

void AMorganKnightSkeletonCharacter::OnWidgetLifeTimeFinished()
{
	HealthWidgetComponent->SetVisibility(false);
}

void AMorganKnightSkeletonCharacter::SpawnLoot() const
{
	if (!HasLoot || !GetWorld()) return;

	FVector CharacterLocation = GetActorLocation();
	CharacterLocation.Z = +50.0f;
	FTransform Transform;
	Transform.SetLocation(CharacterLocation);
	AMorganChestPickUp* Chest = GetWorld()->SpawnActor<AMorganChestPickUp>(LootClass, Transform);
	Chest->SetGoldAmount(Level);
}
