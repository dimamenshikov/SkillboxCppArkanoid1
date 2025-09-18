#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusDecreaseLife.generated.h"

UCLASS()
class ARKANOID_API ABonusDecreaseLife : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreaseLife();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
