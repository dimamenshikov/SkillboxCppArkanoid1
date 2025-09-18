#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerBlock.generated.h"

class ABonus;
class ABlock;

// Тип бонуса и шанс выпадения
USTRUCT(BlueprintType)
struct FBonusTypeChance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABonus> BonusClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax="1"))
	float DropChance = 1.0f;
};

UCLASS()
class ARKANOID_API ASpawnerBlock : public AActor
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ASpawnerBlock();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	//					Gameplay:

	// Variable
private:
	UPROPERTY()
	TArray<UStaticMeshComponent*> Components;
	UPROPERTY()
	TArray<ABlock*> BlockActors;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category ="Components")
	USceneComponent* Scene = nullptr;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	TSubclassOf<ABlock> BlockClass;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	UStaticMesh* Mesh = nullptr;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	FVector Scale = FVector(0.5f, 0.5f, 0.5f);
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	int32 GridSizeX = 5;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	int32 GridSizeY = 5;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	int32 SpacerX = 5;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	int32 SpacerY = 5;
	UPROPERTY(EditAnywhere, Category ="Setting|Game", meta = (ClampMin = "0.0", ClampMax="1"))
	float Difficulty = 0.5f;
	UPROPERTY(EditAnywhere, Category ="Setting|Game", meta = (ClampMin = "0.0", ClampMax="1"))
	float BonusChance = 0.5f;
	UPROPERTY(EditAnywhere, Category ="Setting|Base")
	TArray<FBonusTypeChance> BonusTypeChance;

	// Function	
private:
	UFUNCTION()
	void OnBlockDestroyed(AActor* DestroyedBlock);

	TSubclassOf<ABonus> GetBonusClass() const;
	void CreateComponent();
	void ClearComponents();
	void SpawnBlock();
};
