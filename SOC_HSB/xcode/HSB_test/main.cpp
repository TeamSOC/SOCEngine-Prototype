//
//  main.cpp
//  HSB_test
//
//  Created by hsb0818 on 13. 10. 5..
//  Copyright (c) 2013년 Teraphonia. All rights reserved.
//

#include "../../pch/pch.h"

using namespace SOC_Memory;
int main(int argc, const char * argv[])
{
    Allocator allocator(0, 1, 3, 8, 1024);

    int maxSize = 5;
    int threadID = -1;
    int* pN = (int*)allocator.Alloc( sizeof(int) * maxSize, 0);
    
    for (int i=0; i<maxSize; i++)
        pN[i] = i+1;
    
    for (int i=0; i<maxSize; ++i)
        printf("%d ", pN[i]);
    printf("\n");
    
    allocator.Free(pN, 0, threadID);
    
    printf("%d", threadID);
    
    return 0;
}