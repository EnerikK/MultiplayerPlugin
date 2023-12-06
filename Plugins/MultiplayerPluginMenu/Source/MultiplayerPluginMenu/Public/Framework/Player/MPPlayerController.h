// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameFramework/PlayerController.h"
#include "MPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGINMENU_API AMPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMPPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void OnPossess(APawn* InPawn) override;
	void ShowMenu(const TSoftClassPtr<UCommonActivatableWidget>& MenuClass);
	
};
