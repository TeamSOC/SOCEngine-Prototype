#pragma once

#if defined(_WIN32) || defined(_WIN64)
/*
	#pragma comment(lib, "Ws2_32.lib")
	#pragma comment(lib, "mswsock.lib") 
	
	#include <winsock2.h>
	#include <MSWSock.h>
	#include <ws2tcpip.h>
	#include <iphlpapi.h>
	#include <process.h>
	#include <commctrl.h>
*/
	#include <windows.h>
#else
	//
#endif

//////////////
// this is.... I will use only [std::min, std::max] function.
#undef min
#undef max
//////////////

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <string>
#include <stack>

#include "../System/Queue.h"
//#include "../Lock\Lock.h"
#include "../Memory\Interface.h"