// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "ShootingStarHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSTAR_API AShootingStarHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootingStarHUD();

	TMap<FString, UUserWidget> WidgetMap;
	UUserWidget* CurrentWidget;

	void OpenWidget(FString WidgetName);

};
