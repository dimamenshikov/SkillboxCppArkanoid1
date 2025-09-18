#include "Bonus/BonusTemporary/BonusShuriken.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"
#include "World/Block.h"

//					Parent:

ABonusShuriken::ABonusShuriken()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusShuriken::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->OnBallHit.AddDynamic(this, &ABonusShuriken::Shuriken);
		OldScale = Paddle->CurrentBall->GetActorScale3D();
		OldStaticMesh = Paddle->CurrentBall->StaticMesh->GetStaticMesh();
		OldMaterial = Paddle->CurrentBall->StaticMesh->GetMaterial(0);
		Paddle->CurrentBall->StaticMesh->SetStaticMesh(ShurikenMesh);
		Paddle->CurrentBall->StaticMesh->SetMaterial(0, ShurikenMaterial);
		Paddle->CurrentBall->SetActorScale3D(FVector(0.2f));
	}
}

void ABonusShuriken::ResetData()
{
	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->SetActorScale3D(OldScale);
		Paddle->CurrentBall->StaticMesh->SetStaticMesh(OldStaticMesh);
		Paddle->CurrentBall->StaticMesh->SetMaterial(0, OldMaterial);
	}

	Super::ResetData();
}

void ABonusShuriken::Shuriken(const FHitResult& HitResult)
{
	if (auto Block = Cast<ABlock>(HitResult.GetActor()))
	{
		Block->Exterminate();
	}
	if (!HitResult.GetActor())
	{
		Paddle->CurrentBall->NextDirection = Paddle->CurrentBall->CurrentDirection;
		Paddle->CurrentBall->SetActorLocation(Paddle->CurrentBall->NextLocation);
	}
}
