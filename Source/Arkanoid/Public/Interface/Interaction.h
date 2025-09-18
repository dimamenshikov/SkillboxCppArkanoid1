#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

class ABall;

UINTERFACE()
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

class ARKANOID_API IInteraction
{
	GENERATED_BODY()

public:
	virtual void Interaction(ABall* Ball, const FHitResult& HitResult) = 0;
};
