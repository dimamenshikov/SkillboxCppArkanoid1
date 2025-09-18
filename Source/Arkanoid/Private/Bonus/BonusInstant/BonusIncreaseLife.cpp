#include "Bonus/BonusInstant/BonusIncreaseLife.h"
#include "Framework/Paddle.h"

//					Parent:

ABonusIncreaseLife::ABonusIncreaseLife()
{
	TypeBonusByTime = Instant;
	Value = 1.0f;
}

//					Gameplay:

void ABonusIncreaseLife::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	Paddle->SetLives(Value);
}
