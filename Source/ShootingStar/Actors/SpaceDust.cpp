// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceDust.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "ShootingStar/GameFramework/ShootingStarPawn.h"


// Sets default values
ASpaceDust::ASpaceDust()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Box;
	Box->InitBoxExtent(FVector(50.0f, 30.0f, 30.0f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpaceDust::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ASpaceDust::OnOverlapEnd);

	Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MESHBODY(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (MESHBODY.Succeeded()) {
		Mesh->SetStaticMesh(MESHBODY.Object);
	}
	ssIn = false;
}

// Called when the game starts or when spawned
void ASpaceDust::BeginPlay()
{
	Super::BeginPlay();
	dustspeed = 0.1f;
}

// Called every frame
void ASpaceDust::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ss == nullptr) {
		return;
	}
	ss->SetActorScale3D(ss->GetActorScale() + 0.001f);
}

void ASpaceDust::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ss = Cast<AShootingStarPawn>(OtherActor);
	if (ss == nullptr)
		return;
	ssIn = true;
	UE_LOG(LogTemp, Warning, TEXT("in"));
}

void ASpaceDust::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ssIn = false;
	UE_LOG(LogTemp, Warning, TEXT("out"));
}

