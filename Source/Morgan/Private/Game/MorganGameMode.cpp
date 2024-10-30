// Copyrights P.K.

#include "Game/MorganGameMode.h"

#include "Player/MorganCharacterBase.h"
#include "Player/MorganPlayerController.h"

AMorganGameMode::AMorganGameMode()
{
	DefaultPawnClass = AMorganCharacterBase::StaticClass();
	PlayerControllerClass = AMorganPlayerController::StaticClass();
}
