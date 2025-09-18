#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StateGame.generated.h"

UCLASS()
class ARKANOID_API AStateGame : public AGameStateBase
{
	GENERATED_BODY()

private:
	float GameTime = 0.0f;
	bool bGameStarted = false;

public:
	AStateGame();
	virtual void Tick(float DeltaSeconds) override;
	void StartGame();
	void StopGame();
	UFUNCTION(BlueprintPure, Category = "GameState")
	void GetGameTime(int32& Minutes, int32& Seconds, int32& Milliseconds) const;
};
