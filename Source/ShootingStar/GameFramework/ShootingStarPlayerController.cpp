// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarPlayerController.h"
#include "GameFramework/ShootingStarPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

using namespace ELogVerbosity;

AShootingStarPlayerController::AShootingStarPlayerController()
{

}

void AShootingStarPlayerController::OpenWidget(EWidgetName name)
{
	AShootingStarHUD* mHUD = Cast<AShootingStarHUD>(MyHUD);
	if (mHUD != nullptr && mHUD->OpenWidget(name))
	{
		bShowMouseCursor = true;
	}
}

void AShootingStarPlayerController::CloseWidget(EWidgetName name)
{
	AShootingStarHUD* mHUD = Cast<AShootingStarHUD>(MyHUD);
	if (mHUD != nullptr && mHUD->CloseWidget(name))
	{
		bShowMouseCursor = false;
	}
}

void AShootingStarPlayerController::GameOver()
{
	AShootingStarPawn* mPawn = Cast<AShootingStarPawn>(GetPawn());
	mPawn->ClearTimeoverTimer();
	if (mPawn != nullptr) {
		mPawn->Mesh->SetVisibility(false, true);
		OpenWidget(EWidgetName::GAMEOVER);
	}
}

void AShootingStarPlayerController::GoNextLevel()
{
	if (GetWorld()->GetName().Equals(FString("TUNA")))
	{
		using namespace ELogVerbosity;
		UE_LOG(LogTemp, Warning, TEXT("Entered Wormhole"))
		UGameplayStatics::OpenLevel(this, TEXT("TUNA_2"));
	}
	else 
	{
		GameOver();
	}

}

void AShootingStarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;
	
}
