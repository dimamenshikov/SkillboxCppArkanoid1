#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModeGame.generated.h"

UCLASS()
class ARKANOID_API AModeGame : public AGameModeBase
{
	GENERATED_BODY()

public:
	AModeGame();
	virtual void BeginPlay() override;
	void GameStart();
	void GameEnd();
};
