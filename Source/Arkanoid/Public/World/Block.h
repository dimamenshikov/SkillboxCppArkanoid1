#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Block.generated.h"

class ABonus;
class ULifeBlock;

UCLASS()
class ARKANOID_API ABlock : public AActor, public IInteraction
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABlock();

protected:
	virtual void BeginPlay() override;
	virtual void Interaction(ABall* Ball, const FHitResult& HitResult) override;

	//					Gameplay:

	// Variable
public:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	ULifeBlock* LifeComponent = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABonus> BonusClass;

	UMaterialInstanceDynamic* Material = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Setting")
	TArray<UMaterialInterface*> LifeMaterial;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = "Setting")
	int32 Score = 25;

	// Function
public:
	void Exterminate();
};
