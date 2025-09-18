#pragma once

#include "CoreMinimal.h"
#include "Bonus/Bonus.h"
#include "BonusRocket.generated.h"

UCLASS()
class ARKANOID_API ABonusRocket : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusRocket();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;


	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMesh* RocketMesh = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UMaterialInterface* RocketMaterial = nullptr;

	float SpeedShuriken = 500.0f;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;

private:
	void MoveShuriken(); // Двжиение ракеты
};
