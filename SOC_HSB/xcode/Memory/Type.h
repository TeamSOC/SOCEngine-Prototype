#ifndef _BASETSD_H_

#if defined(_WIN64) || defined(_WIN32)
    typedef __int32 SOC_INT32;
    typedef __int64 SOC_INT64;
#else
    typedef uint32_t SOC_INT32;
    typedef uint64_t SOC_INT64;
#endif

#if defined(_WIN64)
    typedef __int64 INT_PTR, *PINT_PTR;
    typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

    typedef __int64 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

    typedef unsigned __int64 SOC_SIZE_T;

#elif defined(_WIN32)
    typedef __int32 INT_PTR, *PINT_PTR;
    typedef unsigned __int32 UINT_PTR, *PUINT_PTR;

    typedef __int32 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int32 ULONG_PTR, *PULONG_PTR;

    typedef unsigned __int32 SOC_SIZE_T;

#elif defined(__APPLE__) // 64 bit
    typedef int64_t INT_PTR, *PINT_PTR;
    typedef uint64_t UINT_PTR, *PUINT_PTR;

    typedef int64_t LONG_PTR, *PLONG_PTR;
    typedef uint64_t ULONG_PTR, *PULONG_PTR;

    typedef uint32_t SOC_SIZE_T;

#elif defined(__MACH__)
    typedef int32_t INT_PTR, *PINT_PTR;
    typedef uint32_t UINT_PTR, *PUINT_PTR;

    typedef int32_t LONG_PTR, *PLONG_PTR;
    typedef uint32_t ULONG_PTR, *PULONG_PTR;

    typedef uint32_t SOC_SIZE_T;

#endif


#endif