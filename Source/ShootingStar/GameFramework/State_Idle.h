// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "State_Idle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTINGSTAR_API UState_Idle : public UPlayerBaseState
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UState_Idle();


	virtual void handleInput(AShootingStarPawn* playercenter) override;

	virtual void update(AShootingStarPawn* playercenter) override;

	virtual void enter(AShootingStarPawn* playercenter) override;

	virtual void ended(AShootingStarPawn* playercenter) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UPROPERTY(VisibleAnywhere, Category = State)
	//	class UPlayerBaseState* temp;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
