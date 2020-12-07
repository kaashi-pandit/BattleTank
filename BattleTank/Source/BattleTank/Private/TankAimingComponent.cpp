#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetTankBarrelRef(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	const auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("Aiming angle is : %s"), *AimAsRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return;

	FVector OutLaunchVelocity{0};
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	const FCollisionResponseParams ResponseParam;
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		ResponseParam
	);

	//UE_LOG(LogTemp, Warning, TEXT("SuggestProjectileVelocity output is : %d") , bHaveAimSolution);

	if (bHaveAimSolution)
	{
		//const auto ThisTankName = GetOwner()->GetName();
		//const auto BarrelLocation = Barrel->GetComponentLocation();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming from %s to %s"), *ThisTankName , *BarrelLocation.ToString(), *HitLocation.ToString());

		const FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Aim sol found"));
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f | No aim sol found"), Time);
	}
}

