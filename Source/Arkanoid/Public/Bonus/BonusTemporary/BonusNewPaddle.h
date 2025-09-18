#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusNewPaddle.generated.h"

UCLASS()
class ARKANOID_API ABonusNewPaddle : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusNewPaddle();

protected:
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMesh* PaddleMesh = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UMaterialInterface* PaddleMaterial = nullptr;

	FTimerHandle TimerPaddle;
	float Speed = 500.0f;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;

private:
	void MovePaddle(); // Движение новой каретки
};
