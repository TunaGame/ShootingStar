// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Idle.h"

// Sets default values for this component's properties
UState_Idle::UState_Idle()
{

	PrimaryComponentTick.bCanEverTick = false;
	mState = EStateEnum::IDLE;
	// ...
}

void UState_Idle::handleInput(AShootingStarPawn* playercenter)
{

}

void UState_Idle::update(AShootingStarPawn* playercenter)
{
	playercenter->AddMovementInput(playercenter->Direction, 1);
}

void UState_Idle::enter(AShootingStarPawn* playercenter)
{
	playercenter->setEffect(mState);
}

void UState_Idle::ended(AShootingStarPawn* playercenter)
{
}



