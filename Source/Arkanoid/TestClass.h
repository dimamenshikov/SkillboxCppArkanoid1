#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestClass.generated.h"

UCLASS()
class ARKANOID_API ATestClass : public AActor
{
	GENERATED_BODY()

private:
	float f = 50.0f;

public:
	ATestClass();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
