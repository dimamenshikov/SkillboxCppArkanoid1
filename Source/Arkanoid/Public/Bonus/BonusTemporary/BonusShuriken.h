#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusShuriken.generated.h"

class ABall;

UCLASS()
class ARKANOID_API ABonusShuriken : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusShuriken();

	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMesh* ShurikenMesh = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UMaterial* ShurikenMaterial = nullptr;

	UStaticMesh* OldStaticMesh = nullptr;
	UMaterialInterface* OldMaterial = nullptr;
	FVector OldScale;

	// Function
protected:
	UFUNCTION()
	void Shuriken(const FHitResult& Hit); // Уничтожение блока при столкновении

	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void ResetData() override;
};
