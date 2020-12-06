#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Name = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("Player controller begin play : %s") , *Name->GetName());
}

ATank* ATankPlayerController::GetControlledTank() const
{
	 return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair() const
{
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Out hit location is : %s") , *OutHitLocation.ToString());
		GetControlledTank()->AimAt(OutHitLocation);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0f);

	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	const auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation , ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		GetLookLocation(LookDirection, OutHitLocation);
	}
	
	return  true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y, 
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	const auto StartLocation = PlayerCameraManager->GetCameraLocation();
	const auto EndLocation = StartLocation + ( LookDirection * LineTraceRange );

	if ( GetWorld()->LineTraceSingleByChannel
		(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility
		)
	)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
} 