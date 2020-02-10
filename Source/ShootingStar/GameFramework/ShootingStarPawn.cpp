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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Sphere;
	Mesh->SetupAttachment(Sphere);
	SpringArm->SetupAttachment(Sphere);
	Camera->SetupAttachment(SpringArm);

	Sphere->SetSphereRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

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

	PlayerInputComponent->BindAxis(TEXT("Shooting"), this, &AShootingStarPawn::Shooting);
}

void AShootingStarPawn::Shooting(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
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