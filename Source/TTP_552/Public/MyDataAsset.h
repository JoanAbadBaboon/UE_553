// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TTP_552_API UMyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public: 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Assets")
	int a = 10;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Assets")
	float f = 10.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Assets")
	FString name = "MyName";
};
