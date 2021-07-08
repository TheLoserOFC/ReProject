#pragma once
#include <iostream>
#include <cstring>
#include <future>
#include "../Utils/mmp/injector/inject.h"
#include "../Utils/json/json.hpp"


const static int LoaderVersion = 1;
std::string user;
std::string expiration;
std::string titles = "Revolution Cheats";

namespace API {

	bool AuthUser(const std::string username, const std::string password);
	void SaveInfo(const std::string username, const std::string password);
	bool AutoLogin();

	enum RequestType {
		OK,
		INVALID_USER,
		INVALID_PASSWORD,
		INVALID_HWID,
		BANNED
	};
	
}





