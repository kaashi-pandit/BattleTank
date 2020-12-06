#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditAnywhere, Category= Setup)
	float MaxDegreePerSecond{20};

	UPROPERTY(EditAnywhere, Category= Setup)
	float MaxElevationDegree{40};

	UPROPERTY(EditAnywhere, Category= Setup)
	float MinElevationDegree{0};
};
