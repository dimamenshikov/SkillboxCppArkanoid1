#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusIncreasePower.generated.h"

UCLASS()
class ARKANOID_API ABonusIncreasePower : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusIncreasePower();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
