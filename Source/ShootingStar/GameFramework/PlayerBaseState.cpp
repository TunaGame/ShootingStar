// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseState.h"

// Sets default values for this component's properties
UPlayerBaseState::UPlayerBaseState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerBaseState::handleInput(AShootingStarPawn* playercenter)
{
	
}

void UPlayerBaseState::update(AShootingStarPawn* playercenter)
{

}

void UPlayerBaseState::enter(AShootingStarPawn* playercenter)
{
}

void UPlayerBaseState::ended(AShootingStarPawn* playercenter)
{
}

// Called when the game starts
void UPlayerBaseState::BeginPlay()
{
	// Super::BeginPlay();

	// ...

}

// Called every frame
void UPlayerBaseState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

