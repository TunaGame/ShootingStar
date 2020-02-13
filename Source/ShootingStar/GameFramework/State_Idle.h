// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "State_Idle.generated.h"


UCLASS()
class SHOOTINGSTAR_API UState_Idle : public UPlayerBaseState
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UState_Idle();
	FTimerHandle GameoverTimerHandle;

	virtual void handleInput(AShootingStarPawn* playercenter) override;
	virtual void update(AShootingStarPawn* playercenter) override;
	virtual void enter(AShootingStarPawn* playercenter) override;
	virtual void ended(AShootingStarPawn* playercenter) override;

		
};
