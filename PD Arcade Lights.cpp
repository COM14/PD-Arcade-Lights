#include "pch.h"
#include <iostream>
#include <Windows.h>


using namespace System;
using namespace System::IO::Ports;

int sync = 0xff, buttons, sides;

int main(array<System::String^>^ args)
{
	HWND hwnd = FindWindowA(NULL, "Hatsune Miku Project DIVA Arcade Future Tone");
	if (hwnd == NULL) {
		std::cout << "can't find the game\n";
		system("pause");
		exit(-1);
	}


	DWORD procID;
	GetWindowThreadProcessId(hwnd, &procID);
	HANDLE handle = OpenProcess(PROCESS_VM_READ, FALSE, procID);
	if (procID == NULL) {
		std::cout << "error\n";
		system("pause");
		exit(-1);
	}


	SerialPort port("COM8", 38400);
	port.Open();
	while (TRUE) {
		HWND hwnd = FindWindowA(NULL, "Hatsune Miku Project DIVA Arcade Future Tone");
		if (hwnd == NULL) {
			array<System::Byte>^ test = { sync,00,00 };
			port.Write(test, 0, 3);
			Sleep(100);
			exit(0);
		}

		ReadProcessMemory(handle, (LPVOID)0x00014119B950, &buttons, sizeof(buttons), 0);
		ReadProcessMemory(handle, (LPVOID)0x000140EDA330, &sides, sizeof(sides), 0);
		sides = sides + 0xc9;
		ReadProcessMemory(handle, (LPVOID)sides, &sides, sizeof(sides), 0);
		array<System::Byte>^ test = { sync,buttons,sides };
		port.Write(test, 0, 3);
		Sleep(6);

	}

}