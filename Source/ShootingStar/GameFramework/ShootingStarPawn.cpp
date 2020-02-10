// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "ShootingStarPawn.h"

// Sets default values
AShootingStarPawn::AShootingStarPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));


	RootComponent = Sphere;
	Mesh->SetupAttachment(Sphere);


	Sphere->SetSphereRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

		// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// CurrentState = EStateEnum::StateOut;
	// PrevState = EStateEnum::StateOut;
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

}

// Called to bind functionality to input
void AShootingStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AShootingStarPawn::Shooting);
}

void AShootingStarPawn::Shooting()
{
	AddMovementInput(GetActorForwardVector(), 1);
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