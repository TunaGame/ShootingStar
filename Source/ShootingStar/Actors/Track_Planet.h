// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
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

	UPROPERTY(Category = "Path", VisibleAnywhere)
	USplineMeshComponent* Spline_Mesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float Spline_Dgree = 0.0;

	void SetupSplineMesh();

	FVector toShootingStarDirection();
	bool InPlanet;
	int32 ShootingStarDirectionPoint;
	FVector ShootingStarDirection[30];


	TEnumAsByte<ESplinePointType::Type> curve = ESplinePointType::Curve;  //SplinePoint Ÿ��
	FSplinePoint Spline_Point[30];
};
