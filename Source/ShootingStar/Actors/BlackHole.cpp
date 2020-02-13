// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ShootingStarPlayerController.h"
#include "GameFramework/ShootingStarPawn.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Box;
	Box->InitBoxExtent(FVector(50.0f, 30.0f, 30.0f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABlackHole::OnOverlapEnd);
	Box->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MESHBODY(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MESHBODY.Succeeded()) {
		Mesh->SetStaticMesh(MESHBODY.Object);
	}
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlackHole::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) {
		return;
	}
	AShootingStarPlayerController* PlayerController = Cast<AShootingStarPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->GameOver();
}

void ABlackHole::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

