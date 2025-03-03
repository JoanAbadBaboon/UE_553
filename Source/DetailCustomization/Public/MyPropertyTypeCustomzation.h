// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"

class FMyPropertyCustomization : public IPropertyTypeCustomization
{
public:
	// Factory function to create an instance of the customization class
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	// Customize header (row in the Details Panel)
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	// Customize the children (expandable area below the property)
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
};

