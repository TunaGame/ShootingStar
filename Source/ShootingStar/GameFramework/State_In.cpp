// Fill out your copyright notice in the Description page of Project Settings.


#include "State_In.h"

// Sets default values for this component's properties
UState_In::UState_In()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UState_In::handleInput(AShootingStarPawn* playercenter)
{

}

void UState_In::update(AShootingStarPawn* playercenter)
{

}

void UState_In::enter(AShootingStarPawn* playercenter)
{
}

void UState_In::ended(AShootingStarPawn* playercenter)
{
}

// Called when the game starts
void UState_In::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UState_In::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

