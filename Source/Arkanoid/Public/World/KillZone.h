#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class ARKANOID_API AKillZone : public AActor
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	AKillZone();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//					Gameplay:

	// Variable
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ForwardArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* KillZone = nullptr;

	// Function
};
