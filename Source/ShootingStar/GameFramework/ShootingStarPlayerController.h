// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ShootingStarHUD.h"
#include "ShootingStarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSTAR_API AShootingStarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShootingStarPlayerController();

	void OpenWidget(EWidgetName name);
	void CloseWidget(EWidgetName name);

	void TEST();
protected:
	virtual void BeginPlay() override;
};
