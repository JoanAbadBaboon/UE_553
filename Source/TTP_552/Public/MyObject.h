// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TTP_552_API UMyObject : public UObject
{
	GENERATED_BODY()

	/**
	 * Called when a property on this object has been modified externally
	 *
	 * @param PropertyThatChanged the property that was modified
	 */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent);
};
