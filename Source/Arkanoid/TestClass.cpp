#include "TestClass.h"

#include "Bonus/BonusInfinitive/BonusNewBall.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ATestClass::ATestClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestClass::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UClass* _class = ABonusNewBall::StaticClass();
	UKismetSystemLibrary::PrintString(GetWorld(),
	                                  UKismetStringLibrary::Conv_BoolToString(
		                                  ABonusNewBall::StaticClass() == ABonus::StaticClass()));
}
