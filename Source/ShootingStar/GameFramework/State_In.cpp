// Fill out your copyright notice in the Description page of Project Settings.


#include "State_In.h"

// Sets default values for this component's properties
UState_In::UState_In()
{

	PrimaryComponentTick.bCanEverTick = false;
	mState = EStateEnum::INORBIT;
	// ...
}

void UState_In::handleInput(AShootingStarPawn* playercenter)
{

}

void UState_In::update(AShootingStarPawn* playercenter)
{	
	//playercenter->Movement->MaxSpeed = playercenter->Movement->MaxSpeed-50.0f;
	playercenter->AddMovementInput(playercenter->Direction, 1);
	if (!(playercenter->GetActorScale().Equals(FVector(0.5f, 0.5f, 0.5f)))) {
		FVector CurrentScale = playercenter->GetActorScale();
		playercenter->SetActorScale3D(CurrentScale - 0.005f);
	}
}

void UState_In::enter(AShootingStarPawn* playercenter)
{
}

void UState_In::ended(AShootingStarPawn* playercenter)
{
	playercenter->Movement->MaxSpeed = 0.0f;
}




