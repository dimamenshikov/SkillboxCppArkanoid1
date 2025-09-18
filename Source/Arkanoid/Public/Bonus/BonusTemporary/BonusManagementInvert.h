#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusManagementInvert.generated.h"

UCLASS()
class ARKANOID_API ABonusManagementInvert : public ABonus
{
	GENERATED_BODY()

public:
	ABonusManagementInvert();

protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void ResetData() override;
};
