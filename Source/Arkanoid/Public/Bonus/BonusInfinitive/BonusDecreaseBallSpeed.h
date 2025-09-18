#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusDecreaseBallSpeed.generated.h"

UCLASS()
class ARKANOID_API ABonusDecreaseBallSpeed : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreaseBallSpeed();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
