#include "World/SpawnerBlock.h"
#include "Bonus/Bonus.h"
#include "Components/LifeBlock.h"
#include "Framework/ModeGame.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Block.h"

//					Parent:

ASpawnerBlock::ASpawnerBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
}

void ASpawnerBlock::CreateComponent()
{
	if (GridSizeX <= 0 || GridSizeY <= 0)
	{
		return;
	}

	const float BlockWidth = Scale.X * 100.0f;
	const float BlockHeight = Scale.Y * 100.0f;
	const float BlockDepth = Scale.Z * 100.0f;

	const float TotalWidth = BlockWidth * GridSizeX + (GridSizeX - 1) * SpacerX;
	const float TotalHeight = BlockHeight * GridSizeY + (GridSizeY - 1) * SpacerY;

	const FVector CenterOffset = FVector((TotalWidth - BlockWidth) / 2, (TotalHeight - BlockHeight) / 2, 0.0f);
	const FTransform ActorTransform = GetActorTransform();

	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			if (Mesh)
			{
				const float X_Offset = x * (BlockWidth + SpacerX);
				const float Y_Offset = y * (BlockHeight + SpacerY);

				const FVector PreviewLocation = FVector(X_Offset, Y_Offset, 0.0f) - CenterOffset;

				const FVector WorldPreviewLocation = ActorTransform.TransformPosition(PreviewLocation);
				FCollisionQueryParams CollisionParameter;
				CollisionParameter.AddIgnoredActor(this);

				const FVector BoxExtent = FVector(BlockWidth * 0.5, BlockHeight * 0.5, BlockDepth * 0.5);
				const bool bBlocked = GetWorld()->OverlapAnyTestByChannel(
					WorldPreviewLocation, GetTransform().GetRotation(),
					ECC_Visibility, FCollisionShape::MakeBox(BoxExtent), CollisionParameter);

				if (bBlocked)
				{
					DrawDebugBox(GetWorld(), WorldPreviewLocation, BoxExtent, ActorTransform.GetRotation(),
					             FColor::Red, false, 10.0f);
				}
				else
				{
					UStaticMeshComponent* PreviewMeshComponent = NewObject<UStaticMeshComponent>(this);
					PreviewMeshComponent->SetStaticMesh(Mesh);
					PreviewMeshComponent->AttachToComponent(GetRootComponent(),
					                                        FAttachmentTransformRules::KeepRelativeTransform);
					PreviewMeshComponent->SetRelativeScale3D(Scale);
					PreviewMeshComponent->SetRelativeLocation(PreviewLocation);
					PreviewMeshComponent->RegisterComponent();
					Components.Add(PreviewMeshComponent);
				}
			}
		}
	}
}

void ASpawnerBlock::ClearComponents()
{
	for (UStaticMeshComponent* Component : Components)
	{
		if (Component)
		{
			Component->DestroyComponent();
		}
	}
	Components.Empty();
}

void ASpawnerBlock::SpawnBlock()
{
	for (UStaticMeshComponent* PreviewMesh : Components)
	{
		if (PreviewMesh)
		{
			const FTransform SpawnTransform = PreviewMesh->GetComponentTransform();
			if (const auto CurrentBlock = GetWorld()->SpawnActor<ABlock>(BlockClass, SpawnTransform))
			{
				const int32 Life = UKismetMathLibrary::RandomFloatInRange(1, CurrentBlock->LifeComponent->MaxLife);
				const auto BonusClass = UKismetMathLibrary::RandomBoolWithWeight(BonusChance)
					                        ? GetBonusClass()
					                        : nullptr;
				CurrentBlock->LifeComponent->Life = Life;
				const float Alpha = static_cast<float>(CurrentBlock->LifeComponent->GetLife() - 1) / (CurrentBlock->
					LifeComponent->MaxLife - 1);
				CurrentBlock->Material->SetVectorParameterValue(
					"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
				CurrentBlock->SetActorScale3D(Scale);
				CurrentBlock->BonusClass = BonusClass;
				CurrentBlock->AttachToComponent(Scene, FAttachmentTransformRules::KeepWorldTransform);
				CurrentBlock->OnDestroyed.AddDynamic(this, &ASpawnerBlock::OnBlockDestroyed);
				BlockActors.Add(CurrentBlock);
			}
		}
	}
}

void ASpawnerBlock::OnBlockDestroyed(AActor* DestroyedBlock)
{
	BlockActors.Remove(Cast<ABlock>(DestroyedBlock));

	if (auto _GameMode = GetWorld()->GetAuthGameMode<AModeGame>(); BlockActors.IsEmpty() && _GameMode)
	{
		_GameMode->GameEnd();
	}
}

void ASpawnerBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ClearComponents();
	CreateComponent();
}

void ASpawnerBlock::BeginPlay()
{
	Super::BeginPlay();

	SpawnBlock();
	ClearComponents();
}

TSubclassOf<ABonus> ASpawnerBlock::GetBonusClass() const
{
	if (!BonusTypeChance.IsEmpty())
	{
		int32 TotalWeight = 0.0f;
		for (const auto& Bonus : BonusTypeChance)
		{
			TotalWeight += Bonus.DropChance * 100;
		}
		int32 Random = UKismetMathLibrary::RandomInteger(32767) % TotalWeight;
		for (const auto& Bonus : BonusTypeChance)
		{
			if (Random < Bonus.DropChance * 100)
			{
				return Bonus.BonusClass;
			}
			else
			{
				Random -= Bonus.DropChance * 100;
			}
		}
		return nullptr;
	}
	return nullptr;
}
