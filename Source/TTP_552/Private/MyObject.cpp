// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

#include "Kismet2/KismetEditorUtilities.h"

void UMyObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	if (UClass* Class = GetClass())  // Get the class of the current object
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(Class->ClassGeneratedBy)) // Get the Blueprint
		{
			FKismetEditorUtilities::CompileBlueprint(Blueprint);
			UE_LOG(LogTemp, Log, TEXT("Compiled Blueprint: %s"), *Blueprint->GetName());
		}
	}
}
