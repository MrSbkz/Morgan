﻿// Copyrights P.K.

#include "Weapon/MorganCannonball.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMorganCannonball::AMorganCannonball()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

void AMorganCannonball::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMorganCannonball::OnProjectileHit);
	SetLifeSpan(LifeTime);
}

void AMorganCannonball::OnProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageAmount,
		GetActorLocation(),
		DamageRadius,
		UDamageType::StaticClass(),
		{GetOwner()},
		this,
		Pawn->GetController(),
		DoFullDamage);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ExplosionFX,
		Hit.ImpactPoint,
		Hit.ImpactNormal.Rotation());

	Destroy();
}
