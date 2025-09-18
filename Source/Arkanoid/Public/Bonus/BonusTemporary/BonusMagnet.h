#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusMagnet.generated.h"

class ABall;

UCLASS()
class ARKANOID_API ABonusMagnet : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusMagnet();

	//					Gameplay:

	// Variable

	// Function
public:
	UFUNCTION()
	void MagnetBall(const FHitResult& HitResult); // Прикрепление шара к каретки

protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
