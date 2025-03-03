// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDataAssetCustomization.h"
#include "DetailLayoutBuilder.h"
#include "PropertyHandle.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FMyDataAssetCustomization::MakeInstance()
{
	return MakeShareable(new FMyDataAssetCustomization);
}

void FMyDataAssetCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get the object being customized
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() == 1)
	{
		UObject* CustomizedObject = Objects[0].Get();

		UClass* Class = CustomizedObject->GetClass();
		
		// Iterate through all properties
		for (TFieldIterator<FProperty> It(Class); It; ++It)
		{
			FProperty* Property = *It;

			// Get the name of the property
			FString PropertyName = Property->GetName();

			// Get the type of the property
			FString PropertyType = Property->GetCPPType();

			

			// Log the property details
			UE_LOG(LogTemp, Log, TEXT("Property Name: %s, Property Type: %s"), *PropertyName, *PropertyType);

			// Add custom widgets (optional)
			IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("CustomCategory");

			
			FString PropertyString;
			TSharedPtr<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(Property->GetFName());
			
			PropertyHandle->GetValueAsDisplayString(PropertyString);
			
			Category.AddCustomRow(FText::FromString("CustomRow"))
				.NameContent()
				[
					SNew(STextBlock).Text(Property->GetDisplayNameText())
				]
				.ValueContent()
				[
					SNew(STextBlock).Text(FText::FromString(PropertyString))
				];
		}
		}
		
		
}
