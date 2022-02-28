// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/GM_Example02.h"

#include "Example02/KF_Example02_Char.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AGM_Example02::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	AKF_Example02_Char* TempCharToCheck = Cast<AKF_Example02_Char>(NewPlayer->GetPawn());
	if(TempCharToCheck)
	{
		return;
	}
	
	if(NewPlayer->GetPawn())
	{
		NewPlayer->GetPawn()->Destroy();
	}

	FTransform tSpawnTransform;
	TArray<AActor*> foundEntries;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKF_Example02_Char::StaticClass(), foundEntries);

	if(foundEntries.Num() > 0)
	{
		tSpawnTransform = foundEntries[0]->GetActorTransform();
	}
	else
	{
		TArray<AActor*> foundPlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundPlayerStarts);
		tSpawnTransform = foundPlayerStarts[0]->GetActorTransform();
	}

	float fTempFloatX = UKismetMathLibrary::RandomBool() ? UKismetMathLibrary::RandomFloatInRange(-50.f, -150.0f) : UKismetMathLibrary::RandomFloatInRange(50.f, 150.0f);
	float fTempFloatY = UKismetMathLibrary::RandomFloatInRange(-50.0f, -150.0f);

	tSpawnTransform.SetLocation((tSpawnTransform.GetLocation() + FVector(fTempFloatX, fTempFloatY, 0.0f)));
	
    FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = NewPlayer;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector TempLoc = tSpawnTransform.GetLocation();
	FRotator TempRot = tSpawnTransform.GetRotation().Rotator();
    AKF_Example02_Char* TempChar = Cast<AKF_Example02_Char>(GetWorld()->SpawnActor(AKF_Example02_Char::StaticClass(), &TempLoc, &TempRot, SpawnInfo));
	NewPlayer->Possess(TempChar);
}
