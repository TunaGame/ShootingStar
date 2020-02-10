// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "ShootingStarPawn.generated.h"
/*
UENUM(BlueprintType)
enum class EStateEnum : uint8
{
	StateIn UMETA(DisplayName = "IN"),
	StateOut UMETA(DisplayName = "OUT")
};
*/
UCLASS()
class SHOOTINGSTAR_API AShootingStarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShootingStarPawn();
	/*
	UPROPERTY(EditAnywhere, DisplayName = "CharacterState")
	EStateEnum CurrentState;

	EStateEnum PrevState;
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shooting(float NewAxisValue);
	/*
	DECLARE_DELEGATE(FStateDelegate)
	FStateDelegate StateDelegate;

	UFUNCTION()
		void OnIn();
	UFUNCTION()
		void OnOut();

	void InStart();
	void OutStart();

	void InEnd();
	void OutEnd();
	*/
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = Visual)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;
	/*
	UPROPERTY(EditAnywhere)
		EStateEnum InOut;
		*/
};
