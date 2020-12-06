#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ThisTank = Cast<ATank>(GetPawn());

	if (ThisTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI controller : %s"), *ThisTank->GetName());	
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No pawn was found"));
	}

	if( GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank found by the AI controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Tank found by the AI controller"));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (ThisTank)
	{
		ThisTank->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetPlayerTank()
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerController)
	{
		const auto TankRef = Cast<ATank>(PlayerController);
		return  TankRef;
	}	
	return nullptr;
}
