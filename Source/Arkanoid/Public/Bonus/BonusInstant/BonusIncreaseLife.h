#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusIncreaseLife.generated.h"

UCLASS()
class ARKANOID_API ABonusIncreaseLife : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusIncreaseLife();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
