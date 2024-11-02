// Copyrights P.K.

#include "AI/Character/MorganKnightSkeletonCharacter.h"

void AMorganKnightSkeletonCharacter::OnDeath()
{
	Super::OnDeath();

	GetMesh()->SetSimulatePhysics(true);
}
