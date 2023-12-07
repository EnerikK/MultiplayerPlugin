// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGINMENU_API UMPUserWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly);
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
