#pragma once

#include "CoreMinimal.h"
#include "Framework/Paddle.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class APaddle;
class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallHit, const FHitResult&, Hit);

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABall();

protected:
	virtual void Tick(const float DeltaSeconds) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	//					Gameplay:

	// Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;
	
	FOnBallHit OnBallHit;
	APaddle* Paddle = nullptr;
	FVector PreviousLocation, NextLocation, CurrentDirection, NextDirection;
	int32 Power = 10;
	float Speed = 1500.0f;
	bool bMovement = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardDirection = nullptr;

	// Function
public:
	void Init(APaddle* OwnerPaddle);

private:
	UFUNCTION(BlueprintCallable)
	void Move(const float DeltaSeconds);
};
