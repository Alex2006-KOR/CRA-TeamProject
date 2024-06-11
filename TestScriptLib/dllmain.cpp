// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "../TestShellApplication/TestScripts/TestApp1.h"
#include "../TestShellApplication/TestScripts/TestApp2.h"
#include "../TestShellApplication/TestScripts/FailTestApp.h"

#include "../TestShellApplication/TestLibraryCommandInvoker.h"


#include <string>
#include <map>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void addTestScript(
    std::map<string, TestScriptInterface*>& mapCommand,
    TestScriptInterface* pstTestScript
    )
{
    auto iterFind = mapCommand.find(pstTestScript->Name());
    if (iterFind != mapCommand.end()) {
        return;
    }

    mapCommand[pstTestScript->Name()] = pstTestScript;
}

extern "C" __declspec(dllexport) void GetTestSciprtList(TestLibCommandInvoker* pstTestLibCommandInvoker, std::map<string, TestScriptInterface*>& mapCommand)
{
    addTestScript(mapCommand, new TestApp1(pstTestLibCommandInvoker));
    addTestScript(mapCommand, new TestApp2(pstTestLibCommandInvoker));
    addTestScript(mapCommand, new FailTestApp(pstTestLibCommandInvoker));
}