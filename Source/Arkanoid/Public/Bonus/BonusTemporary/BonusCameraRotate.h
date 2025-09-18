#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusCameraRotate.generated.h"

UCLASS()
class ARKANOID_API ABonusCameraRotate : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusCameraRotate();

	//					Gameplay:

	// Variable
private:
	FTimerHandle TimerCameraRotate;
	ACameraActor* Camera = nullptr;
	float CameraSpeed = 30.0f;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus = nullptr) override;
	virtual void ResetData() override;

private:
	void CameraRotate(); // Вращение камеры
};
