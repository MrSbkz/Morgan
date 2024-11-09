// Copyrights P.K.

#include "Pickups/MorganChestPickUp.h"
#include "Components/MorganHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/MorganPlayerState.h"

AMorganChestPickUp::AMorganChestPickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->InitSphereRadius(50.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(Collision);
}

void AMorganChestPickUp::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeTime);
}

void AMorganChestPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, 1.0f, 0.0f));
}

void AMorganChestPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;

	if (const UMorganHealthComponent* HealthComponent = Pawn->FindComponentByClass<UMorganHealthComponent>();
		!HealthComponent || HealthComponent->IsDead()) return;

	AMorganPlayerState* PlayerState = Cast<AMorganPlayerState>(Pawn->GetPlayerState());
	if (!PlayerState) return;

	PlayerState->AddGold(GoldAmount);

	Destroy();
}
