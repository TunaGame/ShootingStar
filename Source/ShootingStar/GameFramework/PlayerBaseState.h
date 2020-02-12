// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "ShootingStarPawn.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseState.generated.h"

UCLASS()
class SHOOTINGSTAR_API UPlayerBaseState : public UActorComponent
{
	GENERATED_BODY()

protected:
	EStateEnum mState;


public:
	// Sets default values for this component's properties
	UPlayerBaseState();

	virtual void handleInput(AShootingStarPawn* playercenter);
	virtual void update(AShootingStarPawn* playercenter);
	virtual void enter(AShootingStarPawn* playercenter);
	virtual void ended(AShootingStarPawn* playercenter);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE EStateEnum getState() const { return mState; }

};
