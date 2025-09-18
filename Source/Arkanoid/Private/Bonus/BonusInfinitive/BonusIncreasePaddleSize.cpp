#include "Bonus/BonusInfinitive/BonusIncreasePaddleSize.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Framework/Paddle.h"
#include "Kismet/GameplayStatics.h"

//					Parent:

ABonusIncreasePaddleSize::ABonusIncreasePaddleSize()
{
	Value = 100.0f;
}

//					Gameplay:

void ABonusIncreasePaddleSize::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusIncreasePaddleSize::UpdateBonus()
{
	Super::UpdateBonus();

	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	const FVector PaddleLocation = Paddle->GetActorLocation();
	const float NewSize = (PaddleScale.Y + 0.4f) * 100 + Value;

	if (Paddle && NewSize < Paddle->GameplaySetting.MaxSizePaddle)
	{
		FVector End = FVector(0.0f, NewSize / 2, 0.0f) + PaddleLocation;
		FHitResult Hit;
		const TArray<AActor*> IgnoreActors{Paddle};
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), PaddleLocation, End, TraceTypeQuery1,
		                                      false, IgnoreActors, EDrawDebugTrace::None, Hit, true);
		if (!Cast<AStaticMeshActor>(Hit.GetActor()))
		{
			End = -1 * End + 2 * PaddleLocation;
			UKismetSystemLibrary::LineTraceSingle(GetWorld(), PaddleLocation, End, TraceTypeQuery1,
			                                      false, IgnoreActors, EDrawDebugTrace::None, Hit, true);
		}
		if (Cast<AStaticMeshActor>(Hit.GetActor()))
		{
			const double Distance = PaddleLocation.Y - Hit.Location.Y;
			Paddle->AddActorLocalOffset(FVector(0.0f, (FMath::Abs(Distance) / Distance)
			                                    * FMath::Abs(NewSize / 2 - FMath::Abs(Distance)), 0.0f));
		}
		PaddleScale.Y = NewSize / 100 - 0.4f;
		Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
		Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, NewSize / 2, 25.0f));
	}
}

void ABonusIncreasePaddleSize::ResetData()
{
	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	PaddleScale.Y = Paddle->GameplaySetting.DefaultSizePaddle / 100 - 0.4f;
	Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
	Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, Paddle->GameplaySetting.DefaultSizePaddle / 2, 25.0f));

	Super::ResetData();
}
