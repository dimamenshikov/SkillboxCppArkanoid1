#include "Framework/ModeGame.h"
#include "Framework/StateGame.h"
#include "Framework/PlayerScore.h"
#include "Kismet/KismetSystemLibrary.h"

AModeGame::AModeGame()
{
	GameStateClass = AStateGame::StaticClass();
	PlayerStateClass = APlayerScore::StaticClass();
}

void AModeGame::BeginPlay()
{
	Super::BeginPlay();

	GameStart();
}

void AModeGame::GameStart()
{
	if (auto TempGameState = Cast<AStateGame>(GameState))
	{
		TempGameState->StartGame();
	}
}

void AModeGame::GameEnd()
{
	if (auto TempGameState = Cast<AStateGame>(GameState))
	{
		TempGameState->StopGame();
	}
	
	UKismetSystemLibrary::PrintString(GetWorld(), "Win");
}
