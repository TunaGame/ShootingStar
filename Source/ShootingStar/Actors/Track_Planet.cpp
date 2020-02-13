// Fill out your copyright notice in the Description page of Project Settings.


#include "Track_Planet.h"
#include "ShootingStar\GameFramework\ShootingStarPawn.h"
#include "ShootingStar\GameFramework\PlayerBaseState.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ShootingStar\GameFramework\ShootingStarPlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ATrack_Planet::ATrack_Planet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("ROTATEMOVEMENT"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISON"));

	SphereComponent->InitSphereRadius(350);
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrack_Planet::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATrack_Planet::OnOverlapEnd);
	//Spline->OnComponentHit.AddDynamic(this, &ATrack_Planet::OnHit);


	Mesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MESHBODY(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (MESHBODY.Succeeded())
		Mesh->SetStaticMesh(MESHBODY.Object);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE"));
	Spline->SetupAttachment(RootComponent);
	Spline->RemoveSplinePoint(1);
	SetupSplineMesh();

}

// Called when the game starts or when spawned
void ATrack_Planet::BeginPlay()
{
	Super::BeginPlay();
	//pp = Cast<AShootingStarPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	
}

// Called every frame
void ATrack_Planet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RMovement->RotationRate = FRotator(0.0f, 10.0f, 0.0f);
	
	if (pp != nullptr) {
		if (pp->getPawnState() == EStateEnum::INORBIT) {
			shootingstar_dir = Spline->GetLocationAtSplinePoint(point_num, ESplineCoordinateSpace::Type::World) - pp->GetActorLocation();
			

			if (FVector::Distance(Spline->GetLocationAtSplinePoint(point_num, ESplineCoordinateSpace::Type::World), pp->GetActorLocation()) <= 50.0f && point_num > 0)
			{
				point_num--;
				if (point_num < 0)
					point_num = 0;
				if (point_num == 0) {
					AShootingStarPlayerController* pc = Cast<AShootingStarPlayerController>(GetWorld()->GetFirstPlayerController());
					pc->GameOver();
				}
			}
			pp->ZeroPointDirection = GetActorLocation()- pp->GetActorLocation();
			pp->Direction = shootingstar_dir;
			/*FString Fstring_sm = Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Type::World).ToString();
			FName Fname_sm = FName(*Fstring_sm);
			UE_LOG(LogTemp, Warning, TEXT("ZeroPointDirection : %s"), *Fstring_sm);*/
		}
	}
	
	
	//UE_LOG(LogTemp, Warning, TEXT("ddfs"));
}

void ATrack_Planet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void ATrack_Planet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto ShootingStar = Cast<AShootingStarPawn>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("Collided : %s"), *OtherActor->GetName())
	if (ShootingStar == nullptr) return;

	pp = ShootingStar;
	if (pp == ShootingStar) {
		point_num = Spline->FindInputKeyClosestToWorldLocation(ShootingStar->GetActorLocation());
		ShootingStar->SetState(EStateEnum::INORBIT);
	}
	
	FString Fstring_sm = FString::FromInt(point_num);
	FName Fname_sm = FName(*Fstring_sm);
	//UE_LOG(LogTemp, Warning, TEXT("shortpoint: %s"), *Fstring_sm);

}

void ATrack_Planet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*auto ShootingStar = Cast<AShootingStarPawn>(OtherActor);
	if (pp == ShootingStar) {
		ShootingStar->SetState(EStateEnum::IDLE);
	}*/
	//shootingstar_dir = FVector::ZeroVector;
	if (OtherActor == nullptr) {
		return;
	}
	pp = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("overlapend "));
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
		/*ConstructorHelpers::FObjectFinder<UStaticMesh> MESHSPLINE(TEXT("/Engine/BasicShapes/Sphere.Sphere"));// Mesh설정
		if (MESHSPLINE.Succeeded())
			SplineMesh->SetStaticMesh(MESHSPLINE.Object);*/

		SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMesh->SetForwardAxis(ESplineMeshAxis::Type::Y, true);
		
		SplineMesh->SetupAttachment(Spline);
		
		FVector SP = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
		FVector ST = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
		FVector EP = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);
		FVector ET = Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);
		
		SplineMesh->SetStartAndEnd(SP, ST, EP, ET, true);
		SplineMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		
	}
}

