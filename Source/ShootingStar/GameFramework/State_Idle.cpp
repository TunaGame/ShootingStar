// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Idle.h"

// Sets default values for this component's properties
UState_Idle::UState_Idle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UState_Idle::handleInput(AShootingStarPawn* playercenter)
{

}

void UState_Idle::update(AShootingStarPawn* playercenter)
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("State_Idle"));
}

void UState_Idle::enter(AShootingStarPawn* playercenter)
{
}

void UState_Idle::ended(AShootingStarPawn* playercenter)
{
}


// Called when the game starts
void UState_Idle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UState_Idle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

