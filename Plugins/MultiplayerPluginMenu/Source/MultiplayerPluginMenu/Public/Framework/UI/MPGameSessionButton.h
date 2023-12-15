// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "MPCommonButtonBase.h"
#include "MPGameSessionButton.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPGameSessionButton : public UMPButtonBaseWidget
{
	GENERATED_BODY()

public:

	void SetTextDisplays(const FText& Game, const FText& Map, const FText& Ping, const FText& PlayerCount, const FText& MaxPlayerCount);

protected:

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* MapText;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* PingText;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* PlayerCountText;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* MaxPlayerCountText;
	
};
