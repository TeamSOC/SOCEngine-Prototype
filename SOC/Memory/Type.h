#ifndef _BASETSD_H_

#if defined(_WIN64)
    typedef __int64 INT_PTR, *PINT_PTR;
    typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

    typedef __int64 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

#elif defined(_WIN32)
    typedef __int32 INT_PTR, *PINT_PTR;
    typedef unsigned __int32 UINT_PTR, *PUINT_PTR;

    typedef __int32 LONG_PTR, *PLONG_PTR;
    typedef unsigned __int32 ULONG_PTR, *PULONG_PTR;

#endif

#endif