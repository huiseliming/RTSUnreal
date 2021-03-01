
#include "RTSUnrealEditor.h"

void FRTSUnrealEditorModule::StartupModule()
{
	UE_LOG(LogRTSE, Log, TEXT("RTSUnrealEditorModule Loaded"));
}

void FRTSUnrealEditorModule::ShutdownModule()
{
	UE_LOG(LogRTSE, Log, TEXT("RTSUnrealEditorModule Unload"));
}


IMPLEMENT_MODULE(FRTSUnrealEditorModule, RTSUnrealEditor)
DEFINE_LOG_CATEGORY(LogRTSE);