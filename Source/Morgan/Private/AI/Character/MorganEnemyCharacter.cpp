// Copyrights P.K.

#include "AI/Character/MorganEnemyCharacter.h"

void AMorganEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(Meshes.Num() > 0, TEXT("Meshes map is empty"));

	GetMesh()->SetSkeletalMesh(Meshes.Contains(Level) ? Meshes[Level].LoadSynchronous() : nullptr);
}
