// Hello :)


#include "Framework/UI/MPUserWidget.h"

void UMPUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
	
}
