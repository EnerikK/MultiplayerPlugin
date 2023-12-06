// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "MPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGINMENU_API UMPGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:
	
	UMPGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
