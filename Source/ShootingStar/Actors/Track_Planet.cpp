// Fill out your copyright notice in the Description page of Project Settings.


#include "Track_Planet.h"
#include "Components/StaticMeshComponent.h"
#include <cmath>
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
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
	Spline->RemoveSplinePoint(1);
	SetupSplineMesh();

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

	RMovement->RotationRate = FRotator(0.0f, 10.0f, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("ddfs"));
}

void ATrack_Planet::SetupSplineMesh()
{
	for (int32 i = 0; i < 30; i++) {
		// 궤도포인트 정의
		Spline_Point[i] = FSplinePoint(i + 1, (i + 1) * FVector(FMath::Sin(Spline_Dgree) * 10.0f, FMath::Cos(Spline_Dgree) * 10.0f, 0.0f)
			, FVector(10.0, 10.0, 10.0), FVector(10.0, 10.0, 10.0), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f), curve);
		Spline->AddPoint(Spline_Point[i], true);
		Spline_Dgree += 0.555;

		// 궤도 메쉬추가
		FString Fstring_sm = "SplineMesh" + FString::FromInt(i);   // SplineMeshComponent 이름 설정
		FName Fname_sm = FName(*Fstring_sm);

		USplineMeshComponent* SplineMesh = CreateDefaultSubobject<USplineMeshComponent>(Fname_sm);           // SplineMeshComponent초기화
		ConstructorHelpers::FObjectFinder<UStaticMesh> MESHSPLINE(TEXT("/Engine/BasicShapes/Sphere.Sphere"));// Mesh설정
		if (MESHSPLINE.Succeeded())
			SplineMesh->SetStaticMesh(MESHSPLINE.Object);

		SplineMesh->RegisterComponentWithWorld(this->GetWorld());
		SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMesh->SetForwardAxis(ESplineMeshAxis::Type::X, true);
		SplineMesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);

		FVector SP = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
		FVector ST = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
		FVector EP = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);
		FVector ET = Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);

		SplineMesh->SetStartAndEnd(SP, ST, EP, ET, true);
		SplineMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
}

