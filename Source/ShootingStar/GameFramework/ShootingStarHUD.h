// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "ShootingStarHUD.generated.h"

UENUM(BlueprintType)
enum class EWidgetName : uint8
{
	GAMEOVER UMETA(DisplayName = "Gameover")
};

UCLASS()
class SHOOTINGSTAR_API AShootingStarHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* WidgetPtrToOpen;

public:
	AShootingStarHUD();

	UPROPERTY()
	TMap<EWidgetName, UUserWidget*> WidgetMap;

	void InitializeWidgets();
	bool OpenWidget(EWidgetName name);
	bool CloseWidget(EWidgetName name);
	//GameoverUI - binding Functions
	UFUNCTION(BlueprintCallable)
	void RestartLevel();
};