#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusIncreasePaddleSize.generated.h"

UCLASS()
class ARKANOID_API ABonusIncreasePaddleSize : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusIncreasePaddleSize();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
