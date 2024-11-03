// Copyrights P.K.

#include "AI/Character/MorganKnightSkeletonCharacter.h"
#include "Components/MorganHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/MorganHealthBarWidget.h"

AMorganKnightSkeletonCharacter::AMorganKnightSkeletonCharacter()
{
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
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
