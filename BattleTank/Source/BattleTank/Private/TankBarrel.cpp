#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1,1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = ElevationChange + GetRelativeRotation().Pitch;
	UE_LOG(LogTemp, Warning, TEXT("Elev OLD : %f"), RawNewElevation);
	
	auto Elevation = FMath::Clamp(RawNewElevation , MinElevationDegree, MaxElevationDegree);

	UE_LOG(LogTemp, Warning, TEXT("Elev NEW : %f"), Elevation);
	
	SetRelativeRotation(FRotator(Elevation, 0 ,0));
}
