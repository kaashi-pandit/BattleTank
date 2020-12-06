#pragma once
#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
private:
	void AimTowardsCrossHair() const;
	bool GetSightRayHitLocation( FVector& OutHitLocation ) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
