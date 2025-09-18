#include "Bonus/BonusTemporary/BonusNewPaddle.h"
#include "Engine/StaticMeshActor.h"
#include "Framework/Paddle.h"

//					Parent:

ABonusNewPaddle::ABonusNewPaddle()
{
	TypeBonusByTime = TemporaryByTime;
}

void ABonusNewPaddle::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                                const FHitResult& Hit)
{
	if (Cast<AStaticMeshActor>(Other))
	{
		Speed *= -1;
	}
}

//					Gameplay:

void ABonusNewPaddle::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	SetActorLocation(Paddle->GetActorLocation() - FVector(150.0f, 0.0f, 0.0f));
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	BonusMesh->SetMaterial(0, PaddleMaterial);
	BonusMesh->SetStaticMesh(PaddleMesh);
	BonusMesh->SetCollisionResponseToAllChannels(ECR_Block);

	SetActorScale3D(FVector(0.4f, 3.0f, 0.4f));
	GetWorldTimerManager().SetTimer(TimerPaddle, this, &ABonusNewPaddle::MovePaddle, 0.033333f,
	                                true);
}

void ABonusNewPaddle::MovePaddle()
{
	AddActorLocalOffset(FVector(0.0f, Speed * 0.033333f, 0.0f), true);
}
