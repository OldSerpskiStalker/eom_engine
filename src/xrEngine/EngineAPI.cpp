// EngineAPI.cpp: implementation of the CEngineAPI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EngineAPI.h"
#include "../xrcdb/xrXRC.h"

// #include "securom_api.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void __cdecl dummy(void){};
CEngineAPI::CEngineAPI()
{
    hGame = 0;
    hRender = 0;
    hTuner = 0;
    pCreate = 0;
    pDestroy = 0;
    tune_pause = dummy;
    tune_resume = dummy;
}

CEngineAPI::~CEngineAPI() {}

extern u32 renderer_value; // con cmd

ENGINE_API bool is_enough_address_space_available()
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    return (*(u32*)&system_info.lpMaximumApplicationAddress) > 0x90000000;
}

void CEngineAPI::Initialize(void)
{
    LPCSTR r4_name;

    if (strstr(Core.Params, "-rstatic"))
    {
        r4_name = "xrRender_R1.dll";
    }
    else
    {
        r4_name = "xrRender_R4.dll";
    }

    Log("Loading DLL:", r4_name);
    hRender = LoadLibrary(r4_name);
    R_ASSERT2(hRender, "Can't setup renderer");

    Device.ConnectToRender();

    // game
    {
        LPCSTR g_name = "xrGame.dll";
        Log("Loading DLL:", g_name);
        hGame = LoadLibrary(g_name);
        if (0 == hGame)
            R_CHK(GetLastError());
        R_ASSERT2(hGame, "Game DLL raised exception during loading or there is no game DLL at all");
        pCreate = (Factory_Create*)GetProcAddress(hGame, "xrFactory_Create");
        R_ASSERT(pCreate);
        pDestroy = (Factory_Destroy*)GetProcAddress(hGame, "xrFactory_Destroy");
        R_ASSERT(pDestroy);
    }
    // йобани кампылятор этого студия
    //////////////////////////////////////////////////////////////////////////
    // vTune
    tune_enabled = FALSE;
    if (strstr(Core.Params, "-tune"))
    {
        LPCSTR g_name = "vTuneAPI.dll";
        Log("Loading DLL:", g_name);
        hTuner = LoadLibrary(g_name);
        if (0 == hTuner)
            R_CHK(GetLastError());
        R_ASSERT2(hTuner, "Intel vTune is not installed");
        tune_enabled = TRUE;
        tune_pause = (VTPause*)GetProcAddress(hTuner, "VTPause");
        R_ASSERT(tune_pause);
        tune_resume = (VTResume*)GetProcAddress(hTuner, "VTResume");
        R_ASSERT(tune_resume);
    }
}

void CEngineAPI::Destroy(void)
{
    if (hGame)
    {
        FreeLibrary(hGame);
        hGame = 0;
    }
    if (hRender)
    {
        FreeLibrary(hRender);
        hRender = 0;
    }
    pCreate = 0;
    pDestroy = 0;
    Engine.Event._destroy();
    XRC.r_clear_compact();
}

extern "C" {
typedef bool __cdecl SupportsAdvancedRendering(void);
typedef bool _declspec(dllexport) SupportsDX10Rendering();
typedef bool _declspec(dllexport) SupportsDX11Rendering();
};
