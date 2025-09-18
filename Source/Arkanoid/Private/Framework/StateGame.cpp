#include "Framework/StateGame.h"

AStateGame::AStateGame()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStateGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameStarted)
	{
		GameTime += DeltaTime;
	}
}

void AStateGame::StartGame()
{
	bGameStarted = true;
}

void AStateGame::StopGame()
{
	bGameStarted = false;
}

void AStateGame::GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const
{
	Minutes = static_cast<int32>(GameTime) / 60;
	Seconds = static_cast<int32>(GameTime) % 60;
	Milliseconds = static_cast<int32>(GameTime - FMath::Floor(GameTime)) * 1000;
}