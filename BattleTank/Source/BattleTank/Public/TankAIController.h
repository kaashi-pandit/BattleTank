#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"

#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ATank* GetPlayerTank();
	ATank* ThisTank = nullptr;
};
