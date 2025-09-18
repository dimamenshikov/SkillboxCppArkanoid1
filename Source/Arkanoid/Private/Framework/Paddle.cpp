#include "Framework/Paddle.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Ball.h"

//					Parent:

APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(BoxCollisionRoot);
	GameplaySetting.DefaultSizePaddle = FMath::Max(GameplaySetting.DefaultSizePaddle, 40.0f);
	BoxCollisionRoot->SetBoxExtent(FVector(20.0f, FMath::Abs(GameplaySetting.DefaultSizePaddle / 2), 25.0f));
	BoxCollisionRoot->SetCollisionProfileName("BlockAll");
	BoxCollisionRoot->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollisionRoot->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static MEsh"));
	StaticMesh->SetupAttachment(BoxCollisionRoot);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	LeftStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftStatic MEsh"));
	LeftStaticMesh->SetupAttachment(StaticMesh);
	LeftStaticMesh->AddRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	LeftStaticMesh->SetAbsolute(false, false, true);
	LeftStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	RightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightStatic MEsh"));
	RightStaticMesh->SetupAttachment(StaticMesh);
	RightStaticMesh->AddRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	RightStaticMesh->SetAbsolute(false, false, true);
	RightStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
	Arrow->AddRelativeLocation(FVector(150.0f, 0.0f, 0.0f));
	Arrow->SetAbsolute(false, false, true);
}

void APaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GameplaySetting.DefaultSizePaddle = FMath::Max(GameplaySetting.DefaultSizePaddle, 40.0f);
	StaticMesh->SetWorldScale3D(FVector(0.4f, FMath::Max(0, GameplaySetting.DefaultSizePaddle / 100 - 0.4f), 0.5f));
	BoxCollisionRoot->SetBoxExtent(FVector(20.0f, FMath::Abs(GameplaySetting.DefaultSizePaddle / 2), 25.0f));
	const FVector TempScale = FVector(StaticMesh->GetComponentScale().X, StaticMesh->GetComponentScale().X,
	                                  StaticMesh->GetComponentScale().Z);
	LeftStaticMesh->SetWorldScale3D(TempScale);
	RightStaticMesh->SetWorldScale3D(TempScale);
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (const auto System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()))
		{
			System->AddMappingContext(Management, 0);
		}
	}

	SpawnBall();
	SpawnBallLives();
}

void APaddle::Interaction(ABall* Ball, const FHitResult& HitResult)
{
	const double BallHitLocation = Ball->GetActorLocation().Y;
	const double PaddleCenter = GetActorLocation().Y - (StaticMesh->GetComponentScale().Y * 50 + 20);

	double Alpha = FMath::Clamp((BallHitLocation - PaddleCenter) / (StaticMesh->GetComponentScale().Y * 100 + 40), 0.0f,
	                            1.0f);
	Alpha = (2.0f + 2.0f / 3.0f) * FMath::Pow(Alpha, 3) - 4.0f * FMath::Pow(Alpha, 2) + (2.0f + 1.0f / 3.0f) * Alpha;

	double Rotate = FMath::Lerp(-70.0f, 70.0f, Alpha);

	if (FMath::Abs(Rotate) < 0.25f)
	{
		Rotate = 0.0f;
	}
	Ball->NextDirection = UKismetMathLibrary::Quat_RotateVector(FQuat(FRotator(0.0f, Rotate, 0.0f)),
	                                                            FVector::ForwardVector);
}

//					PaddleBody:

void APaddle::SpawnBallLives()
{
	if (!Meshes)
	{
		return;
	}

	for (auto BallLife : BallLives)
	{
		BallLife->DestroyComponent();
	}
	BallLives.Empty();

	for (int32 i = 0; i < Lives - 1; ++i)
	{
		if (UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(
			this, *FString::Printf(TEXT("LifeMesh %d"), i + 1)))
		{
			NewMeshComponent->SetStaticMesh(Meshes);
			NewMeshComponent->SetAbsolute(false, false, true);
			NewMeshComponent->SetWorldScale3D(FVector(0.5f));
			NewMeshComponent->SetupAttachment(StaticMesh);
			NewMeshComponent->RegisterComponent();
			NewMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
			BallLives.Add(NewMeshComponent);
		}
	}

	UpdateBallLives();
}

void APaddle::UpdateBallLives()
{
	if (!BallLives.IsEmpty())
	{
		constexpr float BallSpacing = 30.0f;
		const int8 NumBalls = BallLives.Num();

		const float TotalWidth = (NumBalls - 1) * BallSpacing;
		const float StartOffset = -TotalWidth / 2;

		for (int8 i = 0; i < NumBalls; ++i)
		{
			const float Offset = StartOffset + i * BallSpacing;
			if (IsValid(BallLives[i]))
			{
				BallLives[i]->SetRelativeLocation(FVector(-100.0f, Offset, 0.0f));
			}
		}
	}
}

//					Management:

void APaddle::Quit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Menu", true);
}

void APaddle::Start()
{
	SpawnBall();
	if (CurrentBall && CurrentBall->bMovement == false)
	{
		CurrentBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentBall->bMovement = true;
	}
	else
	{
		OnAction.Broadcast();
	}
}

void APaddle::Move(const FInputActionValue& Value)
{
	const FVector2D VectorMove = Value.Get<FVector2D>();
	if (Controller)
	{
		const float MoveSpeed = VectorMove.X * PaddleSpeed * GetWorld()->DeltaTimeSeconds;
		AddActorLocalOffset(FVector(0.0f, MoveSpeed, 0.0f), true);
	}
}

void APaddle::SpawnBall()
{
	if (BallClass && !CurrentBall && Lives)
	{
		const FVector SpawnLocation = Arrow->GetComponentLocation();
		const FRotator SpawnRotation = Arrow->GetComponentRotation();

		if (CurrentBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation); CurrentBall)
		{
			CurrentBall->OnDestroyed.AddDynamic(this, &APaddle::BallDead);
			CurrentBall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			CurrentBall->Init(this);
		}
	}
}

void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Quit, ETriggerEvent::Started, this, &APaddle::Quit);
		EnhancedInputComponent->BindAction(IA_Start, ETriggerEvent::Started, this, &APaddle::Start);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APaddle::Move);
	}
}

//					Gameplay:

void APaddle::BallDead(AActor* Destroyed)
{
	CurrentBall = nullptr;
	Lives = FMath::Max(Lives - 1, 0);
	if (Lives)
	{
		OnBallDead.Broadcast();
		Bonuses.Empty();

		BallLives[Lives - 1]->DestroyComponent();
		BallLives.RemoveAt(Lives - 1);
		UpdateBallLives();
		SpawnBall();
	}
}

void APaddle::SetLives(const int32 Value)
{
	Lives = FMath::Max(0, Lives + Value);
	if (Lives)
	{
		SpawnBallLives();
	}
}
