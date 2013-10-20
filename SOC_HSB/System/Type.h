#pragma once

#pragma warning(disable: 4819)

#if defined(_WIN64) || defined(_WIN32)
    typedef __int32 SOC_INT32;
    typedef __int64 SOC_INT64;
	typedef unsigned __int32 SOC_UINT32;
	typedef unsigned __int64 SOC_UINT64;

    typedef HANDLE SOC_HANDLE;
#else
    typedef int32_t SOC_INT32;
    typedef int64_t SOC_INT64;
	typedef uint32_t SOC_UINT32;
	typedef uint64_t SOC_UINT64;

    typedef pthread_t SOC_HANDLE;
#endif

#if defined(_WIN64)
    typedef __int64 SOC_INT, *SOC_PINT;
    typedef unsigned __int64 USOC_INT, *PUSOC_INT;

    typedef __int64 SOC_LONG, *PSOC_LONG;
    typedef unsigned __int64 SOC_ULONG, *SOC_PULONG;

    typedef unsigned __int64 SOC_SIZE_T;

#elif defined(_WIN32)
	typedef __int32 SOC_INT, *SOC_PINT;
	typedef unsigned __int32 SOC_UINT, *SOC_PUINT;
    
	typedef __int32 SOC_LONG, *PSOC_LONG;
    typedef unsigned __int32 SOC_ULONG, *SOC_PULONG;

    typedef unsigned __int32 SOC_SIZE_T;

#elif defined(__APPLE__) // 64 bit
    typedef int64_t SOC_INT, *SOC_PINT;
    typedef uint64_t USOC_INT, *PUSOC_INT;

    typedef int64_t SOC_LONG, *PSOC_LONG;
    typedef uint64_t SOC_ULONG, *SOC_PULONG;

    typedef uint32_t SOC_SIZE_T;

#elif defined(__MACH__)
    typedef int32_t SOC_INT, *SOC_PINT;
    typedef uint32_t USOC_INT, *PUSOC_INT;

    typedef int32_t SOC_LONG, *PSOC_LONG;
    typedef uint32_t SOC_ULONG, *SOC_PULONG;

    typedef uint32_t SOC_SIZE_T;

#endif

#if defined(_WIN64) || defined(_WIN32)
    typedef SOC_ULONG LOCK_INT;
#else
    typedef SOC_LONG LOCK_INT;
#endif