#include "Bonus/BonusInfinitive/BonusIncreasePower.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"

//					Parent:

ABonusIncreasePower::ABonusIncreasePower()
{
	Value = 3.0f;
}

//					Gameplay:

void ABonusIncreasePower::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusIncreasePower::UpdateBonus()
{
	Super::UpdateBonus();

	if (Paddle && Paddle->CurrentBall && Paddle->CurrentBall->Power + Value < Paddle->GameplaySetting.MaxPower)
	{
		Paddle->CurrentBall->Power += Value;
	}
}

void ABonusIncreasePower::ResetData()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Power = Paddle->GameplaySetting.DefaultPower;
	}

	Super::ResetData();
}
