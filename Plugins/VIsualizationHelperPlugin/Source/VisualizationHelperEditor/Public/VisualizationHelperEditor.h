#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVisualizationHelperEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void AddBufferVisualizationMaterial();

    void AddViewMode();

    void RegisterViewMode();

};
