// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonTextBlock.h"
#include "MPCommonButtonBase.h"
#include "MPButtonGameWidget.generated.h"

/**
 * 
 */
class UMPButtonGameWidget;

UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPButtonGameWidget : public UMPButtonBaseWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	void SetGameData(const FPrimaryAssetId& GameDataAssetId);
	void UpdateButtonText(const FText& GameMapText,const FText& GameNameText,const FText& GameDescText);

protected:

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* Name;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* Desc;
	
	
};
