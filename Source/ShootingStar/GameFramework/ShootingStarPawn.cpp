// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingStarPawn.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AShootingStarPawn::AShootingStarPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	RootComponent = Sphere;
	Sphere->SetSphereRadius(34.0f);
	
	Mesh->SetupAttachment(Sphere);
	ConstructorHelpers::FObjectFinder<UStaticMesh> DEFAULT_SPHERE(TEXT("/Engine/BasicShapes/Sphere.Sphere"));// Mesh설정
	if (DEFAULT_SPHERE.Succeeded())
	{
		Mesh->SetStaticMesh(DEFAULT_SPHERE.Object);
	}
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(Sphere);
	TopDownCameraComponent->SetRelativeLocationAndRotation(FVector(0, 0, 1800.0f), FRotator(-90.f, 0.f, 0.f));
	TopDownCameraComponent->SetAbsolute(true, true, true);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void AShootingStarPawn::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AShootingStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(Direction, 1);
}

// Called to bind functionality to input
void AShootingStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AShootingStarPawn::Shooting);
}

void AShootingStarPawn::Shooting()
{
	Direction.Y = 1.0f;
}
/*
void AShootingStarPawn::OnIn()
{
	// 시간이 지날 때 마다 체력이 깎임, 작아짐
}

void AShootingStarPawn::OnOut()
{
}

void AShootingStarPawn::InStart()
{
	if (StateDelegate.IsBound())
	{
		StateDelegate.Unbind();
	}
	StateDelegate.BindUFunction(this, "OnIn");

}

void AShootingStarPawn::OutStart()
{
	if (StateDelegate.IsBound())
	{
		StateDelegate.Unbind();
	}
	StateDelegate.BindUFunction(this, "OnOut");

}

void AShootingStarPawn::InEnd()
{
}

void AShootingStarPawn::OutEnd()
{
}
*/