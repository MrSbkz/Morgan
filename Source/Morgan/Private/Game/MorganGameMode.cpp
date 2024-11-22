// Copyrights P.K.

#include "Game/MorganGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MorganPlayerCharacter.h"
#include "Player/MorganPlayerController.h"
#include "Player/MorganPlayerState.h"
#include "UI/MorganHUD.h"

AMorganGameMode::AMorganGameMode()
{
	DefaultPawnClass = AMorganPlayerCharacter::StaticClass();
	PlayerControllerClass = AMorganPlayerController::StaticClass();
	HUDClass = AMorganHUD::StaticClass();
	PlayerStateClass = AMorganPlayerState::StaticClass();
}

void AMorganGameMode::RespawnRequest(const int32 RespawnTime)
{
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&AMorganGameMode::RespawnTimerUpdate,
		1.0f,
		true);
}

bool AMorganGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if(PauseSet)
	{
		OnGameStateChanged.Broadcast(EGameState::Pause);
	}

	return PauseSet;
}

bool AMorganGameMode::ClearPause()
{
	const bool IsUnpaused = Super::ClearPause();

	if(IsUnpaused)
	{
		OnGameStateChanged.Broadcast(EGameState::InProgress);
	}

	return IsUnpaused;
}

void AMorganGameMode::RespawnTimerUpdate()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const AMorganHUD* MorganHUD = Cast<AMorganHUD>(PlayerController->GetHUD());
	if(!MorganHUD) return;

	--RespawnCountDown;

	MorganHUD->UpdateRespawnTimer(RespawnCountDown);
	
	if (RespawnCountDown == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		RespawnPlayer(PlayerController);
	}
}

void AMorganGameMode::RespawnPlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
}
