#include "VisualizationHelperEditor.h"

#define LOCTEXT_NAMESPACE "FVisualizationHelperEditorModule"

void FVisualizationHelperEditorModule::StartupModule()
{
	//AddBufferVisualizationMaterial();
	AddViewMode();
}

void FVisualizationHelperEditorModule::ShutdownModule()
{
    
}

void FVisualizationHelperEditorModule::AddBufferVisualizationMaterial()
{
	// Path to DefaultEngine.ini
	const FString ConfigFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultEngine.ini"));
	const FString SectionName = TEXT("Engine.BufferVisualizationMaterials");

	// Key and Value for the custom buffer visualization material
	const FString KeyName = TEXT("CustomBufferVisualization");
	const FString MaterialPath = TEXT("(Material=\"/Game/Materials/MyCustomMaterial.MyCustomMaterial\", Name=LOCTEXT(\"CustomBufferVisualization\", \"Custom Visualization\"))");

	// Find or create the config file
	FConfigFile* ConfigFile = GConfig->FindConfigFile(ConfigFilePath);

	if (!ConfigFile)
	{
		ConfigFile = &GConfig->Add(ConfigFilePath, FConfigFile());
		ConfigFile->Read(ConfigFilePath);
	}

	if (ConfigFile)
	{
		// Check if the key already exists to avoid duplicates
		FString ExistingValue;
		if (!ConfigFile->GetString(*SectionName, *KeyName, ExistingValue))
		{
			// Add the new material entry
			ConfigFile->SetString(*SectionName, *KeyName, *MaterialPath);

			// Write the changes back to the file
			ConfigFile->Write(ConfigFilePath);

			UE_LOG(LogTemp, Log, TEXT("Added %s to [%s] in %s"), *KeyName, *SectionName, *ConfigFilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s already exists in [%s] in %s"), *KeyName, *SectionName, *ConfigFilePath);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to modify %s"), *ConfigFilePath);
	}
}

void FVisualizationHelperEditorModule::AddViewMode()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FVisualizationHelperEditorModule::RegisterViewMode));
}

void FVisualizationHelperEditorModule::RegisterViewMode()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolbar.View");

	FToolMenuSection& Section = Menu->AddSection("CustomViewModes", LOCTEXT("CustomViewModes", "Custom View Modes"));

	Section.AddMenuEntry(
		"My New Custom View",
		LOCTEXT("MyNewCustomView", "My New Custom View"),
		LOCTEXT("MyCustomViewTooltip", "Switch custom view mode node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([]() {
				// Implement logic to apply your custom view
				UE_LOG(LogTemp, Warning, TEXT("My Custom View Mode Button Pressed"));
			})
		)
	);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FVisualizationHelperEditorModule, VisualizationHelperEditor)