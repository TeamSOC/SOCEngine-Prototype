#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#pragma comment(lib, "Ws2_32.lib")
	#pragma comment(lib, "mswsock.lib") 
	
	#include <winsock2.h>
	#include <MSWSock.h>
	#include <ws2tcpip.h>
	#include <iphlpapi.h>
	#include <process.h>
	#include <commctrl.h>
	#include <windows.h>
    #include <conio.h>
    #include <tchar.h>
#else
    #include <unistd.h>
    #include <pthread.h>
    #include <assert.h>
#endif

//////////////
// this is.... I will use only [std::min, std::max] function.
#undef min
#undef max
//////////////

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <limits>

#include <map>
#include <vector>
#include <string>
#include <stack>

#include "../System/Interface.h"
#include "../Memory/Interface.h"