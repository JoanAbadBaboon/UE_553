// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FMyDataAssetCustomization : public IDetailCustomization
{
	
public:
	
	// Factory method to create an instance of this customization
	static TSharedRef<IDetailCustomization> MakeInstance();

	// Customization entry point
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
};
