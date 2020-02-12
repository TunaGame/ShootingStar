// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "ShootingStarPawn.generated.h"

UENUM()
enum class EStateEnum : uint8
{
	IDLE,
	INORBIT,
	STOP
};

UCLASS()
class SHOOTINGSTAR_API AShootingStarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShootingStarPawn();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FVector Direction;
	FVector ZeroPointDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shooting();

public:
	// Called every frame
	void SetState(EStateEnum NewState);
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = Visual)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* Movement;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	class UPlayerBaseState* PlayerBaseState;
	class UState_In* StateIn;
	class UState_Idle* StateIdle;
<<<<<<< HEAD
	// EStateEnum getPawnState() const;
=======
	class UState_Stop* StateStop;

	EStateEnum getPawnState();
>>>>>>> 301bc883f7f779d78241b2441d74ae95a5c4e04e
};
