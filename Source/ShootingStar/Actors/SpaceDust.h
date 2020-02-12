// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpaceDust.generated.h"

UCLASS()
class SHOOTINGSTAR_API ASpaceDust : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceDust();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Actor", VisibleAnywhere)
	float dustspeed;

private:
	UPROPERTY(Category = "Actor", VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY(Category = "Actor", VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	class AShootingStarPawn* ss;

	bool ssIn;

};
