#include "pch.h"
#include <Windows.h>
#include "PluginConfigApi.h"
#include "framework.h"
#define sync 0xff
#define offset 0xc9
using namespace System;
using namespace System::IO::Ports;


uint32_t Rate;
uint8_t Selected_Port, Delay;

void loadConfig()
{
    Selected_Port = GetPrivateProfileIntW(L"general", L"COM Port", 8, CONFIG_FILE);
    Rate = GetPrivateProfileIntW(L"general", L"Rate", 38400, CONFIG_FILE);
    Delay = GetPrivateProfileIntW(L"general", L"Delay", 1, CONFIG_FILE);
    return;
}

void onAttach()
{

    int sides, buttons, ob, os;
    SerialPort port("COM8", Rate);
    HWND hwnd = FindWindowA(NULL, "Hatsune Miku Project DIVA Arcade Future Tone");
    for (; hwnd == NULL; hwnd = FindWindowA(NULL, "Hatsune Miku Project DIVA Arcade Future Tone") ) {Sleep(6000);}

    try{port.Open();}
    catch (...){printf("[PD Arcade Lights] failed to open port\n"); return;}
    printf("[PD Arcade Lights] connected\n");

    while (port.IsOpen == true) {
        memcpy((void*)&buttons, (LPVOID)0x00014119B950, sizeof(buttons));
        memcpy((void*)&sides, (LPVOID)0x000140EDA330, sizeof(sides));
        sides = sides + offset;
        memcpy((void*)&sides, (LPVOID)sides, sizeof(sides));
       
        array<System::Byte>^ out = { sync,buttons,sides };
        if(os!=sides || ob!=buttons) port.Write(out, 0, 3);
        os = sides;
        ob = buttons;
        Sleep(Delay);
    }
    port.Close();
}


BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        loadConfig();
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)onAttach, NULL, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


PluginConfig::PluginConfigOption config[] = {
    { PluginConfig::CONFIG_GROUP_START, new PluginConfig::PluginConfigGroupData{ L"Settings", 110 } },
    { PluginConfig::CONFIG_NUMERIC, new PluginConfig::PluginConfigNumericData{ L"Selected_Port", L"general", CONFIG_FILE, L"COM Port(not working)", L"set to 8", 8, 1, 256} },
    { PluginConfig::CONFIG_DROPDOWN_NUMBER, new PluginConfig::PluginConfigDropdownNumberData{ L"Rate", L"general", CONFIG_FILE, L"Data rate", L"COM Port data rate", 38400, std::vector<int>({ 9600, 38400, 115200 }), false } },
    { PluginConfig::CONFIG_NUMERIC, new PluginConfig::PluginConfigNumericData{ L"Delay", L"general", CONFIG_FILE, L"Delay(ms)", L"Delay between scans (0-100ms)\n0 is not recommended", 1, 0, 100} },
};


extern "C" __declspec(dllexport) LPCWSTR GetPluginName(void)
{
    return L"PD Arcade Lights";
}

extern "C" __declspec(dllexport) LPCWSTR GetPluginDescription(void)
{

    return  L"rets.str()";
}

extern "C" __declspec(dllexport) PluginConfig::PluginConfigArray GetPluginOptions(void)
{
    return PluginConfig::PluginConfigArray{ _countof(config), config };
}


