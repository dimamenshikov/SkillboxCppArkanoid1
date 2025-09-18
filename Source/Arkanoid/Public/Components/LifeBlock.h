#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeBlock.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKANOID_API ULifeBlock : public UActorComponent
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ULifeBlock();

	//					Gameplay:

	// Variable
public:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLife = 0;
	UPROPERTY(EditDefaultsOnly)
	int32 Life = 0;

	// Function
public:
	void Damage(const int32 Damage = 1);
	void SetLife(int32 NewLife);
	FORCEINLINE int32 GetLife() const { return Life; }
	FORCEINLINE bool IsAlive() const { return Life > 0; }
};
