// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingStarPawn.h"
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "PlayerBaseState.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTINGSTAR_API UPlayerBaseState : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerBaseState();

	UFUNCTION()
		virtual void handleInput(AShootingStarPawn* playercenter);
	UFUNCTION()
		virtual void update(AShootingStarPawn* playercenter);
	UFUNCTION()
		virtual void enter(AShootingStarPawn* playercenter);
	UFUNCTION()
		virtual void ended(AShootingStarPawn* playercenter);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
