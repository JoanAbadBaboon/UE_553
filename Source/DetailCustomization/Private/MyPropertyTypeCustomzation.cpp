// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPropertyTypeCustomzation.h"

TSharedRef<IPropertyTypeCustomization> FMyPropertyCustomization::MakeInstance()
{
	return MakeShareable(new FMyPropertyCustomization());
}

void FMyPropertyCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
                                               IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	// Custom header widget
	HeaderRow
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget() // Default name widget
		]
		.ValueContent()
		[
			PropertyHandle->CreatePropertyValueWidget()
		];
}

void FMyPropertyCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
												 IDetailChildrenBuilder& ChildBuilder, 
												 IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	//Here we get a referect to your UDataAsset
	UObject* FoundUObject; 
	PropertyHandle->GetValue(FoundUObject);

	if (FoundUObject)
	{
		TArray<UObject*> Objects;
		Objects.Add(FoundUObject);
		
		UClass* Class = FoundUObject->GetClass();
		
		// Iterate through all properties
		for (TFieldIterator<FProperty> It(Class); It; ++It)
		{
			FProperty* Property = *It;

			//This will add the UDataAsset properties in the details pannel
			IDetailPropertyRow* PropertyRow = ChildBuilder.AddExternalObjectProperty(Objects, Property->GetFName());
			
			int i = 0; 
		}
	}
}

