// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingStarPawn.h"
#include "Components/InputComponent.h"
#include "State_In.h"
#include "State_Idle.h"
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
	ConstructorHelpers::FObjectFinder<UStaticMesh> DEFAULT_SPHERE(TEXT("/Engine/BasicShapes/Sphere.Sphere"));// Mesh¼³Á¤
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

	StateIn = NewObject<UState_In>();
	StateIdle = NewObject<UState_Idle>();

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

	if (PlayerBaseState != nullptr)
	{
		PlayerBaseState->update(this);
	}

}

// Called to bind functionality to input
void AShootingStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AShootingStarPawn::Shooting);
	PlayerInputComponent->BindAction("In", IE_Pressed, this, &AShootingStarPawn::In);
	PlayerInputComponent->BindAction("Out", IE_Pressed, this, &AShootingStarPawn::Out);
}

void AShootingStarPawn::Shooting()
{
	if (PlayerBaseState == nullptr)
	{
		Direction.Y = 1.0f;
		PlayerBaseState = StateIdle;
	}
	else 
	{
		PlayerBaseState->ended(this);
		switch (PlayerBaseState->getState()) {
		case EStateEnum::IDLE :
			PlayerBaseState = StateIn;
			break;
		case EStateEnum::INORBIT :
			PlayerBaseState = StateIdle;
			break;
		}
		PlayerBaseState->enter(this);
	}
}

void AShootingStarPawn::In()
{
	if (PlayerBaseState == nullptr) 
	{
		PlayerBaseState = StateIn;
	}
	else
	{
		PlayerBaseState->ended(this);
		switch (PlayerBaseState->getState())
		{
		case EStateEnum::IDLE :
			PlayerBaseState = StateIn;
			break;
		case EStateEnum::INORBIT :
			PlayerBaseState = StateIn;
			break;
		}
		PlayerBaseState->enter(this);
	}

}

void AShootingStarPawn::Out()
{
	//SetState(EStateEnum::IDLE);
	if (PlayerBaseState == nullptr)
	{
		PlayerBaseState = StateIdle;
	}
	else
	{
		PlayerBaseState->ended(this);
		switch (PlayerBaseState->getState())
		{
		case EStateEnum::IDLE :
			PlayerBaseState = StateIdle;
			break;
		case EStateEnum::INORBIT :
			PlayerBaseState = StateIdle;
			break;
		}
		PlayerBaseState->enter(this);
	}

}
/*
void AShootingStarPawn::SetState(EStateEnum NewState)
{

}
*/