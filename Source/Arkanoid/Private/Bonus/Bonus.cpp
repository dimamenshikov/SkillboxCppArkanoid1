#include "Bonus/Bonus.h"
#include "Framework/Paddle.h"

//					Parent:

ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;
	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	SetRootComponent(BonusMesh);

	BonusMesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ABonus::BeginPlay()
{
	Super::BeginPlay();

	Duration = FMath::Max(GetWorld()->GetDeltaSeconds(), Duration);
	BonusMesh->SetRelativeScale3D(FVector(-1.0f, -2.0f, 0.25f));
}

void ABonus::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (const auto OwnerPaddle = Cast<APaddle>(OtherActor); OwnerPaddle && !bInteractionPaddle)
	{
		bInteractionPaddle = true;
		Paddle = OwnerPaddle;

		if (TypeBonusByTime == TemporaryByCondition || TypeBonusByTime == Instant)
		{
			BonusAction();
			if (TypeBonusByTime == Instant)
			{
				Destroy();
			}
		}
		else
		{
			ABonus* OldBonus = nullptr;
			int32 IndexOldBonus = 0;

			for (IndexOldBonus = 0; IndexOldBonus < Paddle->Bonuses.Num(); ++IndexOldBonus)
			{
				if (Paddle->Bonuses[IndexOldBonus]->GetClass() == GetClass())
				{
					OldBonus = Paddle->Bonuses[IndexOldBonus];
					break;
				}
			}

			if (OldBonus)
			{
				if (bReplaceOldBonus)
				{
					Paddle->Bonuses.RemoveAt(IndexOldBonus);
					Paddle->Bonuses.Add(this);
					BonusAction(OldBonus);
					OldBonus->Destroy();
				}
				else
				{
					OldBonus->UpdateBonus();
					Destroy();
				}
			}
			else
			{
				Paddle->Bonuses.Add(this);
				BonusAction();
			}

			if (TypeBonusByTime == TemporaryByTime)
			{
				GetWorldTimerManager().SetTimer(Timer, this, &ABonus::ResetData, Duration, false);
			}
			Paddle->OnBallDead.AddDynamic(this, &ABonus::ResetData);
		}
	}
}

//					Gameplay:

void ABonus::BonusAction(ABonus* OldBonus)
{
	bMove = false;
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void ABonus::ResetData()
{
	if (Paddle)
	{
		Paddle->Bonuses.Remove(this);
	}
	Destroy();
}

void ABonus::UpdateBonus()
{
	if (TypeBonusByTime == TemporaryByTime)
	{
		GetWorldTimerManager().ClearTimer(Timer);
		GetWorldTimerManager().SetTimer(Timer, this, &ABonus::ResetData, Duration, false);
	}
}

void ABonus::Move(const float DeltaTime)
{
	if (bMove)
	{
		AddActorWorldOffset(VectorMove * BonusSpeed * DeltaTime);
	}
}
