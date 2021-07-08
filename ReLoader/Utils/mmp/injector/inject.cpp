#include "inject.h"
#include "mmap.h"
#include "../../../API/API.hpp"
void inject::pSleep()
{
	Sleep(10000);
}


bool inject::Inject(LPCTSTR process, char* dll)
{
	try {
		WaitForSingleObject(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)pSleep, nullptr, NULL, nullptr), INFINITE);
		PVOID rData = reinterpret_cast<char*>(dll);
		pIDH = (PIMAGE_DOS_HEADER)rData;
		pINH = (PIMAGE_NT_HEADERS)((LPBYTE)rData + pIDH->e_lfanew);
		DWORD pid = MyGetProcessId(process);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		image = VirtualAllocEx(hProcess, NULL, pINH->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		WriteProcessMemory(hProcess, image, rData, pINH->OptionalHeader.SizeOfHeaders, NULL);
		pISH = (PIMAGE_SECTION_HEADER)(pINH + 1);
		for (i = 0; i < pINH->FileHeader.NumberOfSections; i++)
		{
			WriteProcessMemory(hProcess, (PVOID)((LPBYTE)image + pISH[i].VirtualAddress), (PVOID)((LPBYTE)rData + pISH[i].PointerToRawData), pISH[i].SizeOfRawData, NULL);
		}
		mem = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		memset(&ManualInject, 0, sizeof(MANUAL_INJECT));
		ManualInject.ImageBase = image;
		ManualInject.NtHeaders = (PIMAGE_NT_HEADERS)((LPBYTE)image + pIDH->e_lfanew);
		ManualInject.BaseRelocation = (PIMAGE_BASE_RELOCATION)((LPBYTE)image + pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
		ManualInject.ImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((LPBYTE)image + pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
		ManualInject.fnLoadLibraryA = LoadLibraryA;
		ManualInject.fnGetProcAddress = GetProcAddress;
		WriteProcessMemory(hProcess, mem, &ManualInject, sizeof(MANUAL_INJECT), NULL);
		WriteProcessMemory(hProcess, (PVOID)((PMANUAL_INJECT)mem + 1), LoadDll, (DWORD)LoadDllEnd - (DWORD)LoadDll, NULL);
		hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)((PMANUAL_INJECT)mem + 1), mem, 0, NULL);
		WaitForSingleObject(hThread, INFINITE);
		GetExitCodeThread(hThread, &ExitCode);
		return true;
	}
	catch (...) {
		return false;
	}
}