//
//  main.cpp
//  HSB_test
//
//  Created by hsb0818 on 13. 10. 5..
//  Copyright (c) 2013년 Teraphonia. All rights reserved.
//

/*
using namespace SOC_Memory;

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

*/

#include "../../pch/pch.h"

SOC_System::Lock::SpinLock::DefSpinLock slock;
SOC_System::Lock::CriticalSectionLock ccclock;

int i = 0;
int save[1000000] = {0, };
void* test_func(void *data)
{
    int id;
    id = *((int *)data);
    
    while(1)
    {
        {
            {
 //               TYPED_SCOPE_LOCK(ccclock);
            }
 
            {
//                TYPED_SCOPE_SPINLOCK(slock);
            }
            
            printf("%d : %d\n", id, i++);
        }
        
        usleep(100);
    }
}


const int count = 10;
int main(int argc, const char * argv[])
{
    pthread_t p_thread[count];
    int thr_id;
    int status;
    int arr[count];
    
    for (int i=0; i<count; ++i)
    {
        arr[i] = i;
        thr_id = pthread_create(&p_thread[i], NULL, test_func, (void *)&arr[i]);
        if (thr_id < 0)
        {
            perror("thread create error : ");
            exit(0);
        }
    }
    
    for (int i=0; i<count; ++i)
    {
        pthread_join(p_thread[i], (void **)&status);
    }
    
    return 0;
}