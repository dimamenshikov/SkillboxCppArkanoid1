#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/Interaction.h"
#include "Paddle.generated.h"

class UInputMappingContext;
class ABonus;
class ABall;
class UArrowComponent;
class UBoxComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBallDead);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAction);

// Гейплейные характеристики каретки
USTRUCT(BlueprintType)
struct FDataSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DefaultBallSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
	float MinBallSpeed = 500.0f;
	UPROPERTY(EditAnywhere)
	float MaxBallSpeed = 2500.0f;

	UPROPERTY(EditAnywhere)
	float DefaultSizePaddle = 100.0f;
	UPROPERTY(EditAnywhere)
	float MinSizePaddle = 50.0f;
	UPROPERTY(EditAnywhere)
	float MaxSizePaddle = 300.0f;

	UPROPERTY(EditAnywhere)
	int32 DefaultPower = 10;
	UPROPERTY(EditAnywhere)
	int32 MinPower = 5;
	UPROPERTY(EditAnywhere)
	int32 MaxPower = 20;
};

UCLASS()
class ARKANOID_API APaddle : public APawn, public IInteraction
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	APaddle();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Interaction(ABall* Ball, const FHitResult& HitResult) override;

	//					PaddleBody:  

	// Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollisionRoot = nullptr;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftStaticMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightStaticMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Meshes = nullptr;

	TArray<UStaticMeshComponent*> BallLives;

	//Function
private:
	void SpawnBallLives();
	void UpdateBallLives();

	//					Management:

	// Variable
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting|Input", meta = (AllowPrivateAccess=true))
	UInputMappingContext* Management = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting|Input", meta = (AllowPrivateAccess=true))
	UInputAction* IA_Quit = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting|Input", meta = (AllowPrivateAccess=true))
	UInputAction* IA_Start = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setting|Input", meta = (AllowPrivateAccess=true))
	UInputAction* IA_Move = nullptr;

	//Function
private:
	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Start();
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void SpawnBall();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//					Gameplay:

	//Variable
public:
	UPROPERTY(EditDefaultsOnly, Category = "Setting | Game")
	float BallSpeed = 2000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setting | Game")
	float PaddleSpeed = 2000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setting | Game")
	int32 Lives = 3;
	UPROPERTY(BlueprintReadOnly)
	TArray<ABonus*> Bonuses;
	UPROPERTY(EditAnywhere, Category = "Setting | Game")
	FDataSetting GameplaySetting;

	ABall* CurrentBall = nullptr;
	FOnBallDead OnBallDead;
	FOnAction OnAction;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setting | Game")
	TSubclassOf<ABall> BallClass = nullptr;

	//Function
public:
	UFUNCTION()
	void BallDead(AActor* Destroyed);

	void SetLives(const int32 Value = 0);
};
