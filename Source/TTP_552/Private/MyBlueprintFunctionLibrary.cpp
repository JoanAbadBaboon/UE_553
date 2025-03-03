// Fill out your copyright notice in the Description page of Project Settings.


#include "TTP_552/Public/MyBlueprintFunctionLibrary.h"

#include "ILevelSequenceEditorToolkit.h"
#include "ISequencer.h"
#include "LevelSequence.h"
#include "MovieScene.h"
#include "SequencerScriptingRange.h"
#include "SequencerTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Subsystems/EditorActorSubsystem.h"

#define LOCTEXT_NAMESPACE "YourNamespace"


void UMyBlueprintFunctionLibrary::AddNewViewmode()
{
	// UToolMenus* ToolMenus = UToolMenus::Get();
	//
	// // Extend the Edit menu
	// UToolMenu* EditMenu = ToolMenus->ExtendMenu("LevelEditor.ViewportToolbar.ViewModes");
	// FToolMenuSection &section = EditMenu->Sections[0];
	// TArray<FToolMenuSection> &Sections = EditMenu->Sections; 
	// TArray<FToolMenuEntry> Blocks = section.Blocks;
	//
	// section.AddMenuEntry(
	// 	"MyPluginAction",
	// 	FText::FromString("Custom Edit Action"),
	// 	FText::FromString("Does something custom."),
	// 	FSlateIcon(),
	// 	FUIAction(FExecuteAction::CreateLambda([]() {
	// 		UE_LOG(LogTemp, Log, TEXT("Edit Menu Custom Action Triggered!"));
	// 	}))
	// );

	FToolMenuOwner Owner; 
	FToolMenuOwnerScoped ToolMenuOwner(Owner);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.ViewMenu");
	FToolMenuSection& Section = Menu->AddSection("CustomViewModes", LOCTEXT("CustomViewModes", "Custom View Modes"));

	Section.AddMenuEntry(
		"MyCustomView",
		LOCTEXT("MyCustomView", "My Custom View"),
		LOCTEXT("MyCustomViewTooltip", "Switch to My Custom View Mode"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([]() {
				// Implement logic to apply your custom view
			})
		)
	);

	Section.AddSubMenu(
	"CustomViewSubMenu",
	LOCTEXT("CustomViewSubMenu", "Advanced Views"),
	LOCTEXT("CustomViewSubMenuTooltip", "Additional custom views"),
	FNewToolMenuDelegate::CreateLambda([](UToolMenu* SubMenu) {
		FToolMenuSection& SubSection = SubMenu->AddSection("AdvancedViewModes");
		SubSection.AddMenuEntry(
			"AdvancedView1",
			LOCTEXT("AdvancedView1", "Advanced View 1"),
			LOCTEXT("AdvancedView1Tooltip", "Switch to Advanced View 1"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateLambda([]() {
					// Implement Advanced View 1 logic
				})
			)
		);
	})
);

	
	int j = 0; 
}

void UMyBlueprintFunctionLibrary::GetAllGuidsFromLevelSequence(FString LevelSequencePath)
{

	//Get Level Sequence by path
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, *LevelSequencePath));
	if(!LevelSequence)
		return;

	//Get the movie scene from the sequencer
	UMovieScene* MovieScene = LevelSequence->GetMovieScene();
	if(!MovieScene)
		return; 	

	//Get all the bindings from the movie scene and add the binding proxies
	const TArray<FMovieSceneBinding>& Bindings = MovieScene->GetBindings(); 

	TArray<FMovieSceneBindingProxy> BindingsProxies;
	
	for(const FMovieSceneBinding& Binding : Bindings)
	{
		FGuid guid = Binding.GetObjectGuid();
		
		BindingsProxies.Add(FMovieSceneBindingProxy(guid, LevelSequence));
	}

	FSequencerScriptingRange SequencerScriptingRange; 
	SequencerScriptingRange.bHasStart = true;
	SequencerScriptingRange.bHasEnd = true;
	SequencerScriptingRange.InclusiveStart = true;
	SequencerScriptingRange.ExclusiveEnd = true; 
		
	
	//Get the objects bounded to the sequence
	TArray<FSequencerBoundObjects> bound_objects  = USequencerToolsFunctionLibrary::GetBoundObjects(GEditor->GetEditorWorldContext().World(), LevelSequence, BindingsProxies, SequencerScriptingRange);

	//I only have that object, so getting it directly
	TArray<TObjectPtr<UObject>> BoundObjs = bound_objects[0].BoundObjects;

	//In my case, I'm getting all the actors of the level to search for it
	UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> Actors = EditorActorSubsystem->GetAllLevelActors();

	AActor* SelectedActor = EditorActorSubsystem->GetSelectedLevelActors()[0]; 

	//Check if the bounded object is in the level editor and return (commented) the binding proxy
	for(TObjectPtr<UObject> BoundObject : BoundObjs)
	{
		for(AActor* LevelActor : Actors)
		{
			if(LevelActor == BoundObject)
			{ 
				UE_LOG(LogTemp, Warning, TEXT("Same object DETECTED"));
				return; 
				//return bound_objects[0].BindingProxy;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("THE OBJECT WAS NOT FOUND"))
	
}

UObject* UMyBlueprintFunctionLibrary::GetLevelActorForBinding(ULevelSequence* Sequence, FGuid Guid)
{
	
#if WITH_EDITOR

	if(Sequence)
		return nullptr; 
	
	if (GEditor)
	{
		IAssetEditorInstance* AssetEditor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(Sequence, false);
		ILevelSequenceEditorToolkit* LevelSequenceEditor = static_cast<ILevelSequenceEditorToolkit*>(AssetEditor);
		TSharedPtr<ISequencer> Sequencer = LevelSequenceEditor ? LevelSequenceEditor->GetSequencer() : nullptr;
 
		UObject* SpawnedObject = Sequencer->FindSpawnedObjectOrTemplate(Guid);
		return SpawnedObject;
	}
#endif
	return nullptr;
}

UClass* UMyBlueprintFunctionLibrary::OwnGetBlueprintParentClassFromAssetTags(UObject* Blueprint, const FAssetData& FA)
{
	UClass* myClass = nullptr;
	UBlueprint* BP = Cast<UBlueprint>(Blueprint);
	if(BP)
	{
		myClass = BP->GetBlueprintParentClassFromAssetTags(FA);
	}

	// Get the Asset Registry
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	// Search for assets of a specific type (e.g., Blueprints)
	FARFilter Filter;
	Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add(FName("/Game/MyFolder")); // Search in a specific folder
	Filter.bRecursivePaths = true; // Include subfolders

	TArray<FAssetData> AssetList;
	AssetRegistry.GetAssets(Filter, AssetList);

	// Print asset names
	for (const FAssetData& AssetData : AssetList)
	{
		UClass* MyClass = BP->GetBlueprintParentClassFromAssetTags(AssetData);
		UE_LOG(LogTemp, Log, TEXT("Found Asset: %s"), *AssetData.AssetName.ToString())
	}
	
	return myClass; 
}
