#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusDecreasePaddleSize.generated.h"

UCLASS()
class ARKANOID_API ABonusDecreasePaddleSize : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreasePaddleSize();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
