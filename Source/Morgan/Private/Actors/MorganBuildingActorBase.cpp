// Copyrights P.K.

#include "Actors/MorganBuildingActorBase.h"
#include "Components/BoxComponent.h"

AMorganBuildingActorBase::AMorganBuildingActorBase()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
}

bool AMorganBuildingActorBase::CanBuild() const
{
	if (IsActive || IsCollisionOverlapped) return false;

	return IsOnGround();
}

void AMorganBuildingActorBase::Activate()
{
	IsActive = true;
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMorganBuildingActorBase::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AMorganBuildingActorBase::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AMorganBuildingActorBase::OnEndOverlap);
	
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMorganBuildingActorBase::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	IsCollisionOverlapped = true;
}

void AMorganBuildingActorBase::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	IsCollisionOverlapped = false;
}

bool AMorganBuildingActorBase::IsOnGround() const
{
	FHitResult OutHit;
	const FVector Start = GetActorLocation();
	const FVector End = Start + FVector(0.0f, 0.0f, -1.0f) * 1.0f;

	const FCollisionQueryParams CollisionParams;

	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
}
