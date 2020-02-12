// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WormholeActor.generated.h"

UCLASS()
class SHOOTINGSTAR_API AWormholeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWormholeActor();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Semisphere;
	UPROPERTY(EditAnywhere)
	class USphereComponent* Collider;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
