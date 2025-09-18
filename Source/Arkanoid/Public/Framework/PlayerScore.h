#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerScore.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChange, int32, PlayerScore);

UCLASS()
class ARKANOID_API APlayerScore : public APlayerState
{
	GENERATED_BODY()

private:
	int32 PlayerScore = 0;

public:
	UPROPERTY(BlueprintAssignable, Category = "PlayerScore")
	FOnPlayerScoreChange OnPlayerScoreChange;
	
	UFUNCTION(BlueprintPure, Category = "PlayerState")
	FORCEINLINE int32 GetPlayerScore() const { return PlayerScore; };

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void ChangePlayerScore(const int32 Amount);
};
