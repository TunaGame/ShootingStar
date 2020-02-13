// Fill out your copyright notice in the Description page of Project Settings.


#include "WormholeActor.h"
#include "ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ShootingStarPawn.h"
#include "GameFramework/ShootingStarPlayerController.h"

// Sets default values
AWormholeActor::AWormholeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetSphereRadius(100.0f);
	RootComponent = Collider;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AWormholeActor::BeginOverlap);

	Semisphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WormholeInside"));
	Semisphere->SetupAttachment(Collider);
	Semisphere->SetRelativeRotation(FRotator(.0f, .0f, 90.0f));
	ConstructorHelpers::FObjectFinder<UStaticMesh> ASSET_SEMISPHERE(TEXT("StaticMesh'/Game/Planets/WormHole/SemiSphere.SemiSphere'"));
	if (ASSET_SEMISPHERE.Succeeded())
	{
		Semisphere->SetStaticMesh(ASSET_SEMISPHERE.Object);
	}

}

void AWormholeActor::BeginOverlap(UPrimitiveComponent * OverlappedComponent, 
		AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult)
{
	AShootingStarPawn* mPawn = Cast<AShootingStarPawn>(OtherActor);
	AShootingStarPlayerController* mController;
	if (mPawn != nullptr && (mController = Cast<AShootingStarPlayerController>(mPawn->GetController())) != nullptr)
	{
		mController->GoNextLevel();
	}
}
