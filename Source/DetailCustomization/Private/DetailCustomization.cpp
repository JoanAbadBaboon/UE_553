#include "DetailCustomization.h"

#include "MyPropertyTypeCustomzation.h"
#include "MyDataAssetCustomization.h"
#include "MyDataAsset.h"

#define LOCTEXT_NAMESPACE "FDetailCustomizationModule"

void FDetailCustomizationModule::StartupModule()
{
	// Register the detail customization
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	/*
	PropertyEditorModule.RegisterCustomClassLayout(
		 // Replace with the class name of your data asset
		 UMyDataAsset::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FMyDataAssetCustomization::MakeInstance)
	);*/

	PropertyEditorModule.RegisterCustomPropertyTypeLayout(
		UMyDataAsset::StaticClass()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyPropertyCustomization::MakeInstance)
		);
}

void FDetailCustomizationModule::ShutdownModule()
{
	// Unregister the customization
	FPropertyEditorModule* PropertyEditorModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor");
	if (PropertyEditorModule)
	{
		//PropertyEditorModule->UnregisterCustomClassLayout(UMyDataAsset::StaticClass()->GetFName());
		PropertyEditorModule->UnregisterCustomPropertyTypeLayout(UMyDataAsset::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDetailCustomizationModule, DetailCustomization)