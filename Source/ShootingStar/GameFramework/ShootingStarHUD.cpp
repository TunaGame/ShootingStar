// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStarHUD.h"
#include "ConstructorHelpers.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AShootingStarHUD::AShootingStarHUD()
{
	InitializeWidgets();
}

void AShootingStarHUD::InitializeWidgets()
{
	//GameOver UI - Reference address hardcoding
	ConstructorHelpers::FClassFinder<UUserWidget> GameWidgetClassBP(TEXT("WidgetBlueprint'/Game/UI/GameoverWidget.GameoverWidget_C'"));
	if (GameWidgetClassBP.Succeeded())
	{
		WidgetMap.Add(EWidgetName::GAMEOVER, CreateWidget<UUserWidget>(GetWorld(), GameWidgetClassBP.Class));
	}
}

bool AShootingStarHUD::OpenWidget(EWidgetName name)
{

	if (WidgetMap.Find(name) != nullptr)
	{
		WidgetPtrToOpen = *(WidgetMap.Find(name));
		if (!WidgetPtrToOpen || !WidgetPtrToOpen->IsValidLowLevelFast())
		{
			return false;
		}

		TArray<UObject*> ReferredToObjects;				//req outer, ignore archetype, recursive, ignore transient
		FReferenceFinder ObjectReferenceCollector(ReferredToObjects, WidgetPtrToOpen, false, true, true, false);
		ObjectReferenceCollector.FindReferences(WidgetPtrToOpen);

		using namespace ELogVerbosity;
		UE_LOG(LogTemp, Warning, TEXT("Reference count : %d"), ReferredToObjects.Num())

		if (!WidgetPtrToOpen->IsInViewport())
		{
			WidgetPtrToOpen->AddToViewport();
			return true;
		}
	}

	return false;
}

bool AShootingStarHUD::CloseWidget(EWidgetName name)
{
	UUserWidget** WidgetPtrToClose;
	if ((WidgetPtrToClose = WidgetMap.Find(name)) != nullptr)
	{
		if ((*WidgetPtrToClose)->IsInViewport())
		{
			(*WidgetPtrToClose)->RemoveFromViewport();
			return true;
		}
	}
	return false;
}

void AShootingStarHUD::RestartLevel()
{
	for (auto It = WidgetMap.CreateConstIterator(); It; ++It)
	{
		CloseWidget(It.Key());
	}
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
