// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MPMenuMultiplayerWidget.generated.h"

class UMPMenuJoinSessionWidget;
class UMPMenuHostSessionWidget;
class UMPButtonBaseWidget;
/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPMenuMultiplayerWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:

	UFUNCTION()
	void OnHostButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnExiButtonClicked();

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* HostButton;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* JoinButton;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* ExitButton;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TSoftClassPtr<UMPMenuHostSessionWidget> HostWidgetClass;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TSoftClassPtr<UMPMenuJoinSessionWidget> JoinWidgetClass;

	
};
