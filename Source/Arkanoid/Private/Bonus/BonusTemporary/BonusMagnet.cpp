#include "Bonus/BonusTemporary/BonusMagnet.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"

//					Parent:

ABonusMagnet::ABonusMagnet()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusMagnet::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->OnBallHit.AddDynamic(this, &ABonusMagnet::MagnetBall);
	}
}

void ABonusMagnet::MagnetBall(const FHitResult& HitResult)
{
	if (Paddle && Paddle == HitResult.GetActor())
	{
		Paddle->CurrentBall->bMovement = false;
		Paddle->CurrentBall->AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
	}
}
