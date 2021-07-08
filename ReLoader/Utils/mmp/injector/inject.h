#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h> 
#include <sddl.h>
#include <accctrl.h>
#include <conio.h>
#include <aclapi.h>

class inject
{
public:
	static bool Inject(LPCTSTR process, char* dll);
	static void pSleep();
};


