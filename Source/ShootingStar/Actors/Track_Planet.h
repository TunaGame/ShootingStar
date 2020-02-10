// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Track_Planet.generated.h"

UCLASS()
class SHOOTINGSTAR_API ATrack_Planet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrack_Planet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(Category = "Path", VisibleAnywhere)
	USplineComponent* Spline;

	UPROPERTY(Category = "Pawn", VisibleAnywhere)
	URotatingMovementComponent* RMovement;

	UPROPERTY(Category = "Pawn", VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Pawn", VisibleAnywhere)
	USphereComponent* SphereComponent;
};
