// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

#include "../TestShellApplication/TestScripts/TestApp1.h"
#include "../TestShellApplication/TestScripts/TestApp2.h"

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

extern "C" __declspec(dllexport) void GetTestSciprtList(TestLibCommandInvoker* pstTestLibCommandInvoker, std::map<string, TestScriptInterface*>& mapCommand)
{
    mapCommand["testapp1"] = new TestApp1(pstTestLibCommandInvoker);
    mapCommand["testapp2"] = new TestApp2(pstTestLibCommandInvoker);
}