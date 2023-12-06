// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "PrimaryGameLayout.h"
#include "MPPrimaryGameLayout.generated.h"

class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPPrimaryGameLayout : public UPrimaryGameLayout
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;


protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonActivatableWidgetStack* GameStack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonActivatableWidgetStack* GameMenuStack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonActivatableWidgetStack* MenuStack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonActivatableWidgetStack* ModalStack;
	
	
	
	
};
