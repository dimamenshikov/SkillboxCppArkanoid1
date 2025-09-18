#include "Bonus/BonusTemporary/BonusCameraRotate.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"

//					Parent:

ABonusCameraRotate::ABonusCameraRotate()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusCameraRotate::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	for (TActorIterator<ACameraActor> _Camera(GetWorld()); _Camera; ++_Camera)
	{
		if (_Camera && _Camera->ActorHasTag("ArkanoidCamera"))
		{
			Camera = *_Camera;
			GetWorldTimerManager().SetTimer(TimerCameraRotate, this, &ABonusCameraRotate::CameraRotate,
			                                0.033333f, true);
			break;
		}
	}
}

void ABonusCameraRotate::ResetData()
{
	if (Camera)
	{
		Camera->SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
	}

	Super::ResetData();
}

void ABonusCameraRotate::CameraRotate()
{
	if (Camera)
	{
		Camera->AddActorWorldRotation(FRotator(0.0f, 0.033333f * CameraSpeed, 0.0f));
	}
}
