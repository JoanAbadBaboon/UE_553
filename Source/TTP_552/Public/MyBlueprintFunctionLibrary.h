// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequence.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TTP_552_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void AddNewViewmode();

	
	UFUNCTION(BlueprintCallable)
	static void GetAllGuidsFromLevelSequence(FString LevelSequencePath);

	UFUNCTION(BlueprintCallable)
	static UObject* GetLevelActorForBinding(ULevelSequence* Sequence, FGuid Guid);

	UFUNCTION(BlueprintCallable)
	static UClass* OwnGetBlueprintParentClassFromAssetTags(UObject* Blueprint, const FAssetData& FA);
};
