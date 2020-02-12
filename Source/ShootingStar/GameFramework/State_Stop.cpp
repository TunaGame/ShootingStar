// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Stop.h"
UState_Stop::UState_Stop()
{
	PrimaryComponentTick.bCanEverTick = false;
	mState = EStateEnum::STOP;

}

void UState_Stop::handleInput(AShootingStarPawn* playercenter)
{
	
}

void UState_Stop::update(AShootingStarPawn* playercenter)
{
	playercenter->Direction.Y = 1.0f;

}

void UState_Stop::enter(AShootingStarPawn* playercenter)
{
}

void UState_Stop::ended(AShootingStarPawn* playercenter)
{
}