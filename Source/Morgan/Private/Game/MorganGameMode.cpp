// Copyrights P.K.

#include "Game/MorganGameMode.h"
#include "AI/Character/MorganKnightSkeletonCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MorganEnemyPlayerStart.h"
#include "Player/MorganPlayerCharacter.h"
#include "Player/MorganPlayerController.h"
#include "Player/MorganPlayerStart.h"
#include "Player/MorganPlayerState.h"
#include "UI/MorganHUD.h"

AMorganGameMode::AMorganGameMode()
{
	DefaultPawnClass = AMorganPlayerCharacter::StaticClass();
	PlayerControllerClass = AMorganPlayerController::StaticClass();
	HUDClass = AMorganHUD::StaticClass();
	PlayerStateClass = AMorganPlayerState::StaticClass();
}

void AMorganGameMode::StartPlay()
{
	Super::StartPlay();

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMorganPlayerStart::StaticClass(), PlayerStarts);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerStarts.Num() > 0)
	{
		PlayerController->StartSpot = PlayerStarts[0];
	}

	RespawnPlayer(PlayerController);

	StartWave();
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

	if (PauseSet)
	{
		OnGameStateChanged.Broadcast(EGameState::Pause);
	}

	return PauseSet;
}

bool AMorganGameMode::ClearPause()
{
	const bool IsUnpaused = Super::ClearPause();

	if (IsUnpaused)
	{
		OnGameStateChanged.Broadcast(EGameState::InProgress);
	}

	return IsUnpaused;
}

void AMorganGameMode::EnemyKilled()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemies Left: %i"), EnemiesLeft - 1);
	if (--EnemiesLeft == 0)
	{
		++CurrentWave;
		GetWorld()->GetTimerManager().SetTimer(
			NextWaveTimerHandle,
			this,
			&AMorganGameMode::NextWaveTimerUpdate,
			1.0f,
			true);
	}
}

void AMorganGameMode::RespawnTimerUpdate()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const AMorganHUD* MorganHUD = Cast<AMorganHUD>(PlayerController->GetHUD());
	if (!MorganHUD) return;

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

void AMorganGameMode::SpawnEnemies(const FWaveEnemiesType EnemiesType)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMorganEnemyPlayerStart::StaticClass(), EnemyPlayerStarts);

	if (!GetWorld()) return;

	int32 EnemiesWithLootAmount = EnemiesType.EnemiesHasLootAmount;

	for (int32 i = 0; i < EnemiesType.EnemiesAmount; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const AActor* StartSpot = GetEnemyStart();
		if (!StartSpot) continue;

		ACharacter* EnemyCharacter = GetWorld()->SpawnActor<ACharacter>(EnemyCharacterClass, StartSpot->GetTransform(), SpawnInfo);
		if (!EnemyCharacter) continue;

		SetEnemy(EnemyCharacter, EnemiesType.EnemiesLevel, EnemiesWithLootAmount > 0);
		--EnemiesWithLootAmount;
	}
}

AActor* AMorganGameMode::GetEnemyStart()
{
	AActor* SpawnSpot = nullptr;
	if (EnemyPlayerStarts.Num() > 0)
	{
		const int32 RandomEnemyStartIndex = FMath::RandRange(0, EnemyPlayerStarts.Num() - 1);
		SpawnSpot = EnemyPlayerStarts[RandomEnemyStartIndex];
		EnemyPlayerStarts.RemoveAt(RandomEnemyStartIndex);
	}

	return SpawnSpot;
}

void AMorganGameMode::SetEnemy(ACharacter* EnemyCharacter, const int32 EnemyLevel, const bool HasLoot)
{
	if (AMorganKnightSkeletonCharacter* KnightSkeletonCharacter =
		Cast<AMorganKnightSkeletonCharacter>(EnemyCharacter))
	{
		KnightSkeletonCharacter->SetLevel(EnemyLevel);
		KnightSkeletonCharacter->SetHasLoot(HasLoot);
	}
}

void AMorganGameMode::StartWave()
{
	if (EnemiesWaves.Num() < CurrentWave) return;
	
	UE_LOG(LogTemp, Display, TEXT("CurrentWave: %i/%i"), CurrentWave, EnemiesWaves.Num());

	for (const auto EnemiesType : EnemiesWaves[CurrentWave - 1].EnemyTypes)
	{
		EnemiesLeft += EnemiesType.EnemiesAmount;
		SpawnEnemies(EnemiesType);
	}
}

void AMorganGameMode::NextWaveTimerUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("Next wave in: %i"), NextWaveCountDown - 1);
	if (--NextWaveCountDown == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(NextWaveTimerHandle);
		NextWaveCountDown = 5;
		StartWave();
	}
}
