#include "Bonus/BonusInfinitive/BonusDecreasePaddleSize.h"
#include "Components/BoxComponent.h"
#include "Framework/Paddle.h"

//					Parent:

ABonusDecreasePaddleSize::ABonusDecreasePaddleSize()
{
	Value = 100.0f;
}

//					Gameplay:

void ABonusDecreasePaddleSize::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusDecreasePaddleSize::UpdateBonus()
{
	Super::UpdateBonus();

	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	const float NewSize = (PaddleScale.Y + 0.4f) * 100 - Value;

	if (NewSize > Paddle->GameplaySetting.MinSizePaddle)
	{
		PaddleScale.Y = NewSize / 100 - 0.4f;
		Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
		Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, NewSize / 2, 25.0f));
	}
}

void ABonusDecreasePaddleSize::ResetData()
{
	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	PaddleScale.Y = Paddle->GameplaySetting.DefaultSizePaddle / 100 - 0.4f;
	Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
	Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, Paddle->GameplaySetting.DefaultSizePaddle / 2, 25.0f));

	Super::ResetData();
}
