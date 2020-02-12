// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingStarPawn.h"
#include "Components/InputComponent.h"
#include "PlayerBaseState.h"
#include "State_In.h"
#include "State_Idle.h"
#include "State_Stop.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialParameterCollection.h"
#include "Misc/Guid.h"

using namespace ELogVerbosity;
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
	// Mesh
	Mesh->SetupAttachment(Sphere);
	ConstructorHelpers::FObjectFinder<UStaticMesh> ASSET_SM_PAWN(TEXT("StaticMesh'/Game/Pawn/SM_Pawn.SM_Pawn'"));// Mesh¼³Á¤
	if (ASSET_SM_PAWN.Succeeded())
	{
		Mesh->SetStaticMesh(ASSET_SM_PAWN.Object);
	}
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	// MaterialParameterCollection
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ASSET_MPC_PAWN(TEXT("MaterialParameterCollection'/Game/Pawn/MPC_Pawn.MPC_Pawn'"));
	if (ASSET_MPC_PAWN.Succeeded())
	{
		mCollection = ASSET_MPC_PAWN.Object;
		UE_LOG(LogTemp, Warning, TEXT("OK"));
	}
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(Sphere);
	TopDownCameraComponent->SetRelativeLocationAndRotation(FVector(0, 0, 1800.0f), FRotator(-90.f, 0.f, 0.f));
	TopDownCameraComponent->SetAbsolute(true, true, true);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	StateIn = NewObject<UState_In>();
	StateIdle = NewObject<UState_Idle>();
	StateStop = NewObject<UState_Stop>();

	PlayerBaseState = StateStop;
}

// Called when the game starts or when spawned
void AShootingStarPawn::BeginPlay()
{
	Super::BeginPlay();
	mCollection->ScalarParameters[0].DefaultValue = .0f;
}
// Called every frame
void AShootingStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerBaseState->update(this);
	if (PlayerBaseState != nullptr)
	{
		//PlayerBaseState->update(this);
	}

}


// Called to bind functionality to input
void AShootingStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shooting", IE_Pressed, this, &AShootingStarPawn::Shooting);
}
/*
EStateEnum AShootingStarPawn::getPawnState() const
{
	return PlayerBaseState->getState();
}
*/

EStateEnum AShootingStarPawn::getPawnState()
{
	return PlayerBaseState->getState();
}

void AShootingStarPawn::Shooting()
{
	if (PlayerBaseState->getState() == EStateEnum::STOP)
	{
		PlayerBaseState = StateIdle;
	}
	else if (PlayerBaseState->getState() == EStateEnum::INORBIT)
	{
		PlayerBaseState->ended(this);
		PlayerBaseState = StateIdle;
		PlayerBaseState->enter(this);
		Direction = -ZeroPointDirection;
	}
}

void AShootingStarPawn::SetState(EStateEnum NewState)
{
	switch (NewState)
	{
	case EStateEnum::IDLE:
		if (PlayerBaseState != nullptr && PlayerBaseState->getState() == EStateEnum::INORBIT)
		{
			PlayerBaseState->ended(this);
			PlayerBaseState = StateIdle;
			PlayerBaseState->enter(this);
		}
		break;
	case EStateEnum::INORBIT:
		if (PlayerBaseState != nullptr && PlayerBaseState->getState() == EStateEnum::IDLE)
		{
			PlayerBaseState->ended(this);
			PlayerBaseState = StateIn;
			PlayerBaseState->enter(this);
		}
		break;
	default:
		break;
	}
}


void AShootingStarPawn::setEffect(EStateEnum NewState)
{
	if (mCollection == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("mCollection is nullptr"))
		return;
	}
	switch (NewState)
	{
	case EStateEnum::IDLE:
		mCollection->ScalarParameters[0].DefaultValue = .0f;
		break;
	case EStateEnum::INORBIT:
		mCollection->ScalarParameters[0].DefaultValue = 1.0f;
		break;
	default:
		break;
	}
}