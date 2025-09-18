#include "Bonus/BonusInstant/BonusSpawnMinBall.h"
#include "Bonus/BonusInfinitive/BonusNewBall.h"
#include "World/Ball.h"

//					Parent:

ABonusSpawnMinBall::ABonusSpawnMinBall()
{
	TypeBonusByTime = Instant;
}

//					Gameplay:

void ABonusSpawnMinBall::BonusAction(ABonus* OldBonus)
{
	if (Ball && Paddle->CurrentBall)
	{
		const FVector BallLocation = Paddle->CurrentBall->GetActorLocation();
		const FRotator BallRotation = Paddle->CurrentBall->GetActorRotation();

		for (int32 i = -1; i < 2; i += 2)
		{
			if (auto _Ball = GetWorld()->SpawnActor<ABall>(
				Ball, BallLocation + Paddle->CurrentBall->GetActorRightVector() * 50.0f * i,
				BallRotation + FRotator(0.0f, 90.0f * i, 0.0f)))
			{
				_Ball->Speed = 2500.0f;
				_Ball->Power = 5;
				_Ball->SetActorScale3D(FVector(0.5f, 0.5, 0.5f));
				_Ball->SetLifeSpan(20.0f);
				_Ball->NextDirection = _Ball->GetActorForwardVector();
				_Ball->bMovement = true;
			}
		}
	}
}
