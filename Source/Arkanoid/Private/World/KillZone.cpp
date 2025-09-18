#include "World/KillZone.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

//					Parent:

AKillZone::AKillZone()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardDirection"));
	ForwardArrow->SetupAttachment(SceneRoot);

	KillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Zone"));
	KillZone->SetupAttachment(SceneRoot);
}

void AKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor!=this)
	{
		OtherActor->Destroy();
	}
}
