// Copyrights P.K.

#include "Components/MorganRespawnComponent.h"
#include "Game/MorganGameMode.h"
#include "Player/MorganPlayerState.h"

void UMorganRespawnComponent::Respawn()
{
	if (!GetWorld()) return;

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if(!Pawn) return;
	
	const AController* Controller = Pawn->GetController();
	if (!Controller) return;

	const AMorganPlayerState* PlayerState = Controller->GetPlayerState<AMorganPlayerState>();
	if(!PlayerState) return;
	
	AMorganGameMode* GameMode = Cast<AMorganGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->RespawnRequest(StartedRespawnTime + PlayerState->GetDeathsCount());
}
