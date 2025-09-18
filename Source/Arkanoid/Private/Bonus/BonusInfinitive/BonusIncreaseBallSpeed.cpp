#include "Bonus/BonusInfinitive/BonusIncreaseBallSpeed.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"

//					Parent:

ABonusIncreaseBallSpeed::ABonusIncreaseBallSpeed()
{
	Value = 300.0f;
}

//					Gameplay:

void ABonusIncreaseBallSpeed::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusIncreaseBallSpeed::UpdateBonus()
{
	Super::UpdateBonus();

	if (Paddle && Paddle->CurrentBall && Paddle->CurrentBall->Speed + Value < Paddle->GameplaySetting.MaxBallSpeed)
	{
		Paddle->CurrentBall->Speed += Value;
	}
}

void ABonusIncreaseBallSpeed::ResetData()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Speed = Paddle->GameplaySetting.DefaultBallSpeed;
	}

	Super::ResetData();
}
