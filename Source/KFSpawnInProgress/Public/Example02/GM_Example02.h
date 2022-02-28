// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Example02.generated.h"

UCLASS()
class KFSPAWNINPROGRESS_API AGM_Example02 : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
};
