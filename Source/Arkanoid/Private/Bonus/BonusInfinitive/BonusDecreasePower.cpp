#include "Bonus/BonusInfinitive/BonusDecreasePower.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"

//					Parent:

ABonusDecreasePower::ABonusDecreasePower()
{
	Value = 2.0f;
}

//					Gameplay:

void ABonusDecreasePower::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusDecreasePower::UpdateBonus()
{
	Super::UpdateBonus();

	if (Paddle && Paddle->CurrentBall && Paddle->CurrentBall->Power - Value > Paddle->GameplaySetting.MinPower)
	{
		Paddle->CurrentBall->Power -= Value;
	}
}

void ABonusDecreasePower::ResetData()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Power = Paddle->GameplaySetting.DefaultPower;
	}

	Super::ResetData();
}
