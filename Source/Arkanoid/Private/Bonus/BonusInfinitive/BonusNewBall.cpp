#include "Bonus/BonusInfinitive/BonusNewBall.h"
#include "Bonus/BonusTemporary/BonusMagnet.h"
#include "Components/ArrowComponent.h"
#include "World/Ball.h"

//					Gameplay:

void ABonusNewBall::StartMove()
{
	for (auto Ball : NewBalls)
	{
		if (Ball && Ball->bMovement == false)
		{
			Ball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Ball->bMovement = true;
			break;
		}
	}
}

void ABonusNewBall::BallDead(AActor* Destroyed)
{
	if (Paddle && Paddle->CurrentBall == Destroyed)
	{
		Paddle->CurrentBall = NewBalls[0];
		NewBalls.RemoveAt(0);

		for (auto Bonus : Paddle->Bonuses)
		{
			if (auto BonusMagnet = Cast<ABonusMagnet>(Bonus))
			{
				Paddle->CurrentBall->OnBallHit.AddDynamic(BonusMagnet, &ABonusMagnet::MagnetBall);
			}
		}
	}
	else
	{
		NewBalls.Remove(Cast<ABall>(Destroyed));
	}
	if (NewBalls.IsEmpty())
	{
		ResetData();
	}
}

void ABonusNewBall::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	Paddle->CurrentBall->OnDestroyed.RemoveDynamic(Paddle, &APaddle::BallDead);
	Paddle->CurrentBall->OnDestroyed.AddDynamic(this, &ABonusNewBall::BallDead);
	Paddle->OnAction.AddDynamic(this, &ABonusNewBall::StartMove);

	UpdateBonus();
}

void ABonusNewBall::UpdateBonus()
{
	Super::UpdateBonus();

	if (auto NewBall = GetWorld()->SpawnActor<ABall>(BallClass, Paddle->Arrow->GetComponentLocation(),
	                                                 Paddle->Arrow->GetComponentRotation()); NewBall && Paddle->
		CurrentBall)
	{
		NewBall->AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
		NewBall->Init(Paddle);
		NewBall->OnDestroyed.AddDynamic(this, &ABonusNewBall::BallDead);
		NewBalls.Add(NewBall);
	}
}

void ABonusNewBall::ResetData()
{
	if (Paddle)
	{
		Paddle->CurrentBall->OnDestroyed.AddDynamic(Paddle, &APaddle::BallDead);
	}

	Super::ResetData();
}
