#include "API.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/json/json.hpp"
#include <stdio.h>
#include <fstream>
#include <direct.h>

using json = nlohmann::json;


void API::SaveInfo(std::string username, std::string password) {

	std::string preset = ("{ \"username\": \"" + username + "\", \"password\": \"" + Utils::AESEncrypt(password, "12345678909876543212345678909875", "1234567890987655") + "\"}");

	_mkdir("C:\\Windows\\Revolution");

	std::ofstream file("C:\\Windows\\Revolution\\RE.bin", std::ios::binary);


	file << preset << std::endl;

	file.close();

	std::ifstream MyFile;

	MyFile.open("C:\\Windows\\Revolution\\RE.bin");
	if (!MyFile) {
		MessageBoxA(NULL, "Erro ao salvar", "Erro", NULL);
		return;
	}
	
}


bool API::AutoLogin() {
	std::ifstream file;
	std::string linha;


	file.open("C:\\Windows\\Revolution\\RE.bin");

	if (!file) return false;

	if (!file.is_open()) return false;



		while (getline(file, linha)) {
			file >> linha;
		}
		try {
			json j;
			j = json::parse(linha);

			std::string username = j["username"];
			std::string password = j["password"];

			if (!API::AuthUser(username, Utils::AESDecrypt(password, "12345678909876543212345678909875", "1234567890987655"))) {
				if (remove("C:\\Windows\\Revolution\\RE.bin") == 0)
					return false;
				else
					return false;
			}

			return API::AuthUser(username, Utils::AESDecrypt(password, "12345678909876543212345678909875", "1234567890987655"));
		}
		catch (...) {
			MessageBoxA(NULL, "An error occurred in AutoLogin, contact an administrator!", "Erro", NULL);
			return false;
		}
	
}

