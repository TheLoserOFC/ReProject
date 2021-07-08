#pragma once
#include <Windows.h>
#include "../Utils/encrypts/CryptoPP/aes.h"
#include "../Utils/encrypts/CryptoPP/osrng.h"
#include "../Utils/encrypts/CryptoPP/cryptlib.h"
#include "../Utils/encrypts/CryptoPP/base64.h"
#include "../Utils/encrypts/CryptoPP/filters.h"
#include "../Utils/encrypts/CryptoPP/modes.h"
#include "../Utils/encrypts/CryptoPP/hex.h"
#include "../Utils/encrypts/CryptoPP/ccm.h"



namespace Utils {

	std::string getHWID();
	std::string AESEncrypt(std::string txt, std::string key, std::string iv);
	std::string AESDecrypt(std::string txt, std::string key, std::string iv);
	bool isRunningAdm(LPCTSTR process);
	bool isRunning(int pid);
	void Inject(LPCTSTR process, char* binary);
	void CloseProcess(LPCTSTR name);
	char* ToChar(std::string name);

}

