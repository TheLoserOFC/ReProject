#include "Utils.hpp"
#include "mmp/injector/inject.h"
#include <future>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cstdint>
#include <iostream>
#include <string>

std::string Utils::getHWID() {
	DWORD lVolSerialNbr = 0;
	char sHDSerial[255] = "";
	GetVolumeInformationA("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, NULL);
	_ultoa_s(lVolSerialNbr, sHDSerial, 10);
	std::string c(sHDSerial);
	return c;
}

DWORD GetProcessId(std::string ProcessName)
{
	HANDLE hsnap;
	PROCESSENTRY32 pt;
	DWORD PiD;
	hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	do {
		if (!strcmp(pt.szExeFile, ProcessName.c_str())) {
			CloseHandle(hsnap);
			PiD = pt.th32ProcessID;
			return PiD;
			if (PiD != NULL) {
				return 0;
			}
		}
	} while (Process32Next(hsnap, &pt));
	return 1;
}

std::string Utils::AESEncrypt(std::string txt, std::string key, std::string iv) {
	std::string cipher_text;

	try {
		CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption;
		encryption.SetKeyWithIV((CryptoPP::byte*)key.c_str(), key.size(), (CryptoPP::byte*)iv.c_str());

		CryptoPP::StringSource encryptor(txt, true,
			new CryptoPP::StreamTransformationFilter(encryption,
				new CryptoPP::Base64Encoder(
					new CryptoPP::StringSink(cipher_text),
					false
				)
			)
		);
	}
	catch (CryptoPP::Exception&) {
		exit(0);
	}
	return cipher_text;
}

std::string Utils::AESDecrypt(std::string txt, std::string key, std::string iv) {
	std::string plain_text;

	try {
		CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption;
		decryption.SetKeyWithIV((CryptoPP::byte*)key.c_str(), key.size(), (CryptoPP::byte*)iv.c_str());

		CryptoPP::StringSource decryptor(txt, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StreamTransformationFilter(decryption,
					new CryptoPP::StringSink(plain_text)
				)
			)
		);
	}
	catch (CryptoPP::Exception& ex) {
		MessageBoxA(0, "Invalid API/Encryption key", "Control", MB_ICONERROR);
		exit(0);
	}
	return plain_text;
}
bool Utils::isRunningAdm(LPCTSTR process) {
	unsigned long aProcesses[1024], cbNeeded, cProcesses;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return false;

	cProcesses = cbNeeded / sizeof(unsigned long);
	for (unsigned int i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] == 0)
			continue;

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, aProcesses[i]);
		char buffer[50];
		GetModuleBaseName(hProcess, 0, buffer, 50);
		CloseHandle(hProcess);
		if (process == std::string(buffer))
			return true;
	}
	return false;
}

bool Utils::isRunning(int pid) {
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}

void Utils::CloseProcess(LPCTSTR process) {

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, process) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

void Utils::Inject(LPCTSTR process, char* binary) {
	if (isRunning(GetProcessId("csgo.exe"))) {
		std::future<bool> a = std::async(inject::Inject, process, binary);

		a.wait();
		bool b = a.get();

	}
	else
		MessageBoxA(NULL, "Process not found!", process, NULL);
}

char* Utils::ToChar(std::string value) {

	char* a = &value[0];

	return a;
}