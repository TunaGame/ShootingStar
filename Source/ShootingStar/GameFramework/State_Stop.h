// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "State_Stop.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSTAR_API UState_Stop : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	UState_Stop();


	virtual void handleInput(AShootingStarPawn* playercenter) override;
	virtual void update(AShootingStarPawn* playercenter) override;
	virtual void enter(AShootingStarPawn* playercenter) override;
	virtual void ended(AShootingStarPawn* playercenter) override;
};
