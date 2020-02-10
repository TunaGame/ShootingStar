// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarGameModeBase.h"
#include "GameFramework/ShootingStarPlayerController.h"
#include "GameFramework/ShootingStarHUD.h"
#include "GameFramework/ShootingStarPawn.h"

AShootingStarGameModeBase::AShootingStarGameModeBase()
{
	DefaultPawnClass = AShootingStarPawn::StaticClass();
	PlayerControllerClass = AShootingStarPlayerController::StaticClass();
	HUDClass = AShootingStarHUD::StaticClass();
}