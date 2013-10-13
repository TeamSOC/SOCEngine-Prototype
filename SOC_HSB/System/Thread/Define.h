//
//  Define.h
//  HSB_test
//
//  Created by SungBin_Hong on 13. 10. 14..
//  Copyright (c) 2013년 Teraphonia. All rights reserved.
//

#pragma once

#if defined(__APPLE__)
    #define InterlockedIncrement(x)     OSAtomicIncrement64( (x) )
    #define InterlockedDecrement(x)     OSAtomicDecrement64( (x) )
    #define InterlockedExchangeAdd(pValue, addNum)      OSAtomicAdd64((addNum), (pValue))
    #define InterlockedExchangeSubtract(pValue, subNum) OSAtomicAdd64(-(subNum), (pValue))
    #define InterlockedCompareExchange(pValue, newNum, oldNum)  OSAtomicCompareAndSwap64((oldNum), (newNum), (pValue))
#elif defined(__MACH__)
    #define InterlockedIncrement(x) OSAtomicIncrement32( (x) )
    #define InterlockedDecrement(x) OSAtomicDecrement32( (x) )
    #define InterlockedExchangeAdd(pValue, addNum)      OSAtomicAdd32((addNum), (pValue))
    #define InterlockedExchangeSubtract(pValue, subNum) OSAtomicAdd32(-(subNum), (pValue))
    #define InterlockedCompareExchange(pValue, newNum, oldNum)  OSAtomicCompareAndSwap32((oldNum), (newNum), (pValue))
#endif