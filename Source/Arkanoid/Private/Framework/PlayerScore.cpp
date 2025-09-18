#include "Framework/PlayerScore.h"

void APlayerScore::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);
	OnPlayerScoreChange.Broadcast(PlayerScore);
}
