#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

class APaddle;

// Тип бонуса в зависимости от длительности действия
UENUM(BlueprintType)
enum ETypeBonusByTime
{
	TemporaryByTime, Infinitive, TemporaryByCondition, Instant
};

UCLASS(Blueprintable, Abstract)
class ARKANOID_API ABonus : public AActor
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonus();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//					Gameplay:

	// Variable
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BonusMesh = nullptr;
	UPROPERTY(EditAnywhere)
	float BonusSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
	float Duration = 10.0f;
	UPROPERTY(EditAnywhere)
	float Value = 10.0f;

	ETypeBonusByTime TypeBonusByTime = Infinitive;
	FTimerHandle Timer;
	APaddle* Paddle = nullptr;
	FVector VectorMove = FVector(-1.0f, 0.0f, 0.0f);
	bool bInteractionPaddle = false;
	bool bReplaceOldBonus = false;

private:
	bool bMove = true;

	// Function
protected:
	UFUNCTION()
	virtual void ResetData(); // Уничтожение бонуса, возвращение персонажу исходных данных 

	virtual void BonusAction(ABonus* OldBonus = nullptr); // Активация бонуса
	virtual void UpdateBonus(); // Обновление бонуса при подборе такого же бонуса

private:
	void Move(const float DeltaTime); // Движение бонуса
};
