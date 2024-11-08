// Copyrights P.K.


#include "Actors/MorganBuildingActorBase.h"


// Sets default values
AMorganBuildingActorBase::AMorganBuildingActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMorganBuildingActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMorganBuildingActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

