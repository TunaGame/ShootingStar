// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingStarPawn.h"
#include "Components/InputComponent.h"
#include "PlayerBaseState.h"
#include "State_In.h"
#include "State_Idle.h"
#include "State_Stop.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ShootingStarPlayerController.h"
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
	//MaterialInstanceDynamic
	//UMaterialInterface* mMaterial = Mesh->GetMaterial(0);
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(Sphere);
	TopDownCameraComponent->SetRelativeLocationAndRotation(FVector(0, 0, 1800.0f), FRotator(-90.f, 0.f, 0.f));
	TopDownCameraComponent->SetAbsolute(true, true, true);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GameoverTimerHandle = FTimerHandle();

	StateIn = NewObject<UState_In>();
	StateIdle = NewObject<UState_Idle>();
	StateStop = NewObject<UState_Stop>();

	StateIn->AddToRoot();
	StateIdle->AddToRoot();
	StateStop->AddToRoot();

	PlayerBaseState = StateStop;
}

// Called when the game starts or when spawned
void AShootingStarPawn::BeginPlay()
{
	Super::BeginPlay();
	setEffect(EStateEnum::IDLE);
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
		PlayerBaseState->enter(this);
	}
	else if (PlayerBaseState->getState() == EStateEnum::INORBIT)
	{
		PlayerBaseState->ended(this);
		PlayerBaseState = StateIdle;
		PlayerBaseState->enter(this);
		Direction = -ZeroPointDirection;
	}
}

void AShootingStarPawn::SetTimeoverTimer()
{
	GetWorldTimerManager().SetTimer(GameoverTimerHandle, this, &AShootingStarPawn::Timeover, TIMEOVER, false);
	UE_LOG(LogTemp, Warning, TEXT("Timer on Set"));
}

void AShootingStarPawn::ClearTimeoverTimer()
{
	if (GetWorldTimerManager().IsTimerActive(GameoverTimerHandle))
	{
		using namespace ELogVerbosity;
		UE_LOG(LogTemp, Warning, TEXT("Clear timer"));
		GetWorldTimerManager().ClearTimer(GameoverTimerHandle);
	}
}

void AShootingStarPawn::Timeover()
{
	GetWorldTimerManager().ClearTimer(GameoverTimerHandle);
	AShootingStarPlayerController* mController = Cast<AShootingStarPlayerController>(GetController());
	if (mController != nullptr)
	{
		mController->GameOver();
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
	if (Mesh == nullptr) return;

	switch (NewState)
	{
	case EStateEnum::IDLE:
		//UE_LOG(LogTemp, Warning, TEXT("IDLE EFFECT"));
		Mesh->SetScalarParameterValueOnMaterials("Burn", .0f);
		break;
	case EStateEnum::INORBIT:
		Mesh->SetScalarParameterValueOnMaterials("Burn", 1.0f);
		//UE_LOG(LogTemp, Warning, TEXT("INORBIT EFFECT"));
		break;
	default:
		break;
	}
}