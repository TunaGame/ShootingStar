// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarPlayerController.h"
#include "Components/SplineMeshComponent.h"
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
	OpenWidget(EWidgetName::GAMEOVER);
	GetPawn()->Destroy();
}

void AShootingStarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;
	
}
