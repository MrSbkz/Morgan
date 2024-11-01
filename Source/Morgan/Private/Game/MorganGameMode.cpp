// Copyrights P.K.

#include "Game/MorganGameMode.h"
#include "Player/MorganPlayerCharacter.h"
#include "Player/MorganPlayerController.h"
#include "UI/MorganHUD.h"

AMorganGameMode::AMorganGameMode()
{
	DefaultPawnClass = AMorganPlayerCharacter::StaticClass();
	PlayerControllerClass = AMorganPlayerController::StaticClass();
	HUDClass = AMorganHUD::StaticClass();
}
