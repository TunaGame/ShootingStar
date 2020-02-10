// Fill out your copyright notice in the Description page of Project Settings.


#include "Track_Planet.h"
#include "Components/StaticMeshComponent.h"
#include <cmath>
#include "UObject/ConstructorHelpers.h"
// Sets default values
ATrack_Planet::ATrack_Planet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE"));
	RMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("ROTATEMOVEMENT"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISON"));

	SphereComponent->InitSphereRadius(3.0);
	RootComponent = SphereComponent;
	
	Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MESHBODY(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (MESHBODY.Succeeded()) 
		Mesh->SetStaticMesh(MESHBODY.Object);
	Spline->SetupAttachment(RootComponent);
	TEnumAsByte<ESplinePointType::Type> curve = ESplinePointType::Curve;
	/*TArray<FSplinePoint> Points;
	Points.Init(FSplinePoint(), 4);
	int a = 0;
	for (int i = 0; i < 4; i++) {
		Points.Add(FSplinePoint(i+1, FVector(i *  100.0f, i * 100.0f, 0.0f), FVector(10.0, 10.0,10.0), FVector(10.0, 10.0, 10.0), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f), curve));
		a += 90;
		if (a >= 360) {
			a = 0;
		}
	}
	Spline->AddPoints(Points, true);*/
	double pi = 2 * acos(0.0);
	float a = 0.0;
	FSplinePoint p[15];
	for (int i = 0; i < 15; i++) {
		p[i] = FSplinePoint(i + 2, (i + 1) * FVector(FMath::Sin(a) * 30.0f,  FMath::Cos(a) * 30.0f, 0.0f), FVector(10.0, 10.0, 10.0), FVector(10.0, 10.0, 10.0), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f), curve);
		Spline->AddPoint(p[i], true);
		a += 1.57;
		if (a >= 6.28) {
			a = 0;
		}
	}
	FSplinePoint s1=FSplinePoint(2.0f, FVector(200.0f, 200.0f, 0.0f), FVector(10.0, 10.0, 10.0), FVector(10.0, 10.0, 10.0), FRotator(0.0f, 0.0f, 0.0f),FVector(1.0f,1.0f,1.0f), curve);
	//Spline->AddPoint(s1, true);
	FSplinePoint s2= FSplinePoint(3.0f, FVector(300.0f, 300.0f, 0.0f), FVector(10.0, 10.0, 10.0), FVector(10.0, 10.0, 10.0), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f), curve);
	//Spline->AddPoint(s2, true);
	/*Points->
	Spline->AddPoints(Points, true);*/
	

	UE_LOG(LogTemp, Warning, TEXT("This is %f"), FMath::Sin(FMath::DegreesToRadians(90)));
	UE_LOG(LogTemp, Warning, TEXT("This is %f"), FMath::Sin(FMath::RadiansToDegrees(3.14)));
	UE_LOG(LogTemp, Warning, TEXT("This is %f"), FMath::DegreesToRadians(FMath::Sin(180)));
	UE_LOG(LogTemp, Warning, TEXT("This is %f"), FMath::RadiansToDegrees(FMath::Sin(90)));
	UE_LOG(LogTemp, Warning, TEXT("This is %f"), FMath::Sin(4.71));

}

// Called when the game starts or when spawned
void ATrack_Planet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrack_Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//UE_LOG(LogTemp, Warning, TEXT("ddfs"));

}

