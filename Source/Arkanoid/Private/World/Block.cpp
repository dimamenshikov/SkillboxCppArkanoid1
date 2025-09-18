#include "World/Block.h"
#include "Bonus/Bonus.h"
#include "Components/LifeBlock.h"
#include "Framework/PlayerScore.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Ball.h"

//					Parent:

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	SetRootComponent(StaticMesh);

	LifeComponent = CreateDefaultSubobject<ULifeBlock>(TEXT("Lives"));
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
	Material = StaticMesh->CreateDynamicMaterialInstance(0);
	const float Alpha = static_cast<float>(LifeComponent->GetLife() - 1) / (LifeComponent->MaxLife - 1);
	Material->SetVectorParameterValue(
		"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
}

void ABlock::Interaction(ABall* Ball, const FHitResult& HitResult)
{
	if (Ball && LifeComponent)
	{
		LifeComponent->Damage(Ball->Power);
		if (!LifeComponent->IsAlive())
		{
			Exterminate();
		}
		else
		{
			const float Alpha = static_cast<float>(LifeComponent->GetLife() - 1) / (LifeComponent->MaxLife - 1);
			Material->SetVectorParameterValue(
				"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
		}
	}
}

//					Gameplay:

void ABlock::Exterminate()
{
	if (const auto World = GetWorld(); BonusClass && World)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor<ABonus>(BonusClass, GetActorLocation(), GetActorRotation());
	}
	if (const auto Pawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Cast<APlayerScore>(Pawn->GetPlayerState())->ChangePlayerScore(Score);
	}
	Destroy();
}
