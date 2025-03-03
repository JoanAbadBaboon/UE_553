#include "ExpandViewmode.h"

#define LOCTEXT_NAMESPACE "FExpandViewmodeModule"

void FExpandViewmodeModule::StartupModule()
{
	FToolMenuOwner Owner; 
	FToolMenuOwnerScoped ToolMenuOwner(Owner);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.ViewMenu");
	FToolMenuSection& Section = Menu->AddSection("CustomViewModes", LOCTEXT("CustomViewModes", "Custom View Modes"));

	Section.AddMenuEntry(
		"MyCustomView",
		LOCTEXT("MyCustomView", "My Custom View"),
		LOCTEXT("MyCustomViewTooltip", "Switch to My Custom View Mode"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([]() {
				// Implement logic to apply your custom view
			})
		)
	);

	Section.AddSubMenu(
	"CustomViewSubMenu",
	LOCTEXT("CustomViewSubMenu", "Advanced Views"),
	LOCTEXT("CustomViewSubMenuTooltip", "Additional custom views"),
	FNewToolMenuDelegate::CreateLambda([](UToolMenu* SubMenu) {
		FToolMenuSection& SubSection = SubMenu->AddSection("AdvancedViewModes");
		SubSection.AddMenuEntry(
			"AdvancedView1",
			LOCTEXT("AdvancedView1", "Advanced View 1"),
			LOCTEXT("AdvancedView1Tooltip", "Switch to Advanced View 1"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateLambda([]() {
					// Implement Advanced View 1 logic
				})
			)
		);
	})
);
}

void FExpandViewmodeModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FExpandViewmodeModule, ExpandViewmode)