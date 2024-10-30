// Copyrights P.K.

#include "Animations/MorganAnimNotify.h"

void UMorganAnimNotify::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
