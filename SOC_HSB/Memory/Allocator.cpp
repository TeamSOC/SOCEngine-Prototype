//
//  Allocator.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#include "../pch/pch.h"

namespace SOC_Memory {
    
    Allocator::Allocator(SOC_INT32 threadID, SOC_INT32 threadMax, SOC_INT32 minAlign, SOC_INT32 maxAlign, SOC_SIZE_T bufferSize)
		: m_threadID(threadID)
		, m_threadMax(threadMax)
		, m_minAlign(minAlign)
		, m_maxAlign(maxAlign)
		, m_allocedMemoryRealSize(0)
		, m_lowWaterMark(std::numeric_limits<SOC_INT32>::max())
	{
		// for instance.. number of between 3 and 10 is not [10 - 3 = 7]. 
		// that is 8.
		m_alignCount = maxAlign - minAlign +1;
		
		m_ppFreeListArray = (CSlab**)malloc(m_alignCount * sizeof(CSlab*));
		for (int i=0; i<m_alignCount; ++i)
		{
			SOC_INT32 align = 1 << (i + minAlign);
			m_ppFreeListArray[i] = new CSlab(align, bufferSize);
		}
	}

    Allocator::~Allocator()
	{
		for (int i=0; i<m_alignCount; ++i)
		{
			if (m_ppFreeListArray[i] == nullptr)
				continue;

			delete m_ppFreeListArray[i];
		}

		SAFE_FREE(m_ppFreeListArray);
	}

	void* Allocator::Alloc(SOC_SIZE_T size, SOC_INT32 tag)
	{
		// note : (thread | size) + tag
        // if 64 bit, following below.
        // size + 4 byte + (2byte | 6 byte)
        // but no RAM memory not supported yet.
        // so i select max allocatable memory is 4GB.
        // size + 4 byte + (1 byte | 3 byte)
        
		SOC_SIZE_T realSize = size + 4 * 2;

		if (OVERFLOWCHECK_ADD(m_allocedMemoryRealSize, realSize))
		{
			return nullptr;
		}

		CSlab* pSlab = GetSlab(realSize);
		m_allocedMemoryRealSize += realSize;

		SOC_INT32* pMem = nullptr;
		if (pSlab != nullptr)
		{
			pMem = (SOC_INT32*)pSlab->GetMemory();
		}
		else
		{
			pMem = (SOC_INT32*)malloc(realSize);
			memset(pMem, FREE_PATTERN, realSize);
		}

		if (pMem == nullptr)
		{
			// memory alloc failed. this is error.
			throw std::bad_alloc();
			return nullptr;
		}

		// in 32 bit, max allocatable : 16777216 byte.
		// this is 2^24 : 3 byte.
		// this form is [we will use byte][tag][threadID | size]
		*pMem = ((m_threadID << THREAD_SHIFT) | size);
		*(pMem +1) = tag & TAG_MASK;

		return CheckAlloc(pMem +2);
	}

	bool Allocator::Free(void* ptr, SOC_INT32 tag, SOC_INT32& ref_ThreadID)
	{
        GarbageCollect();
        
		if (tag != ExtractTag(ptr))
		{
			// note : not matched memory tag
			// tag info have to same
			// crash
			return false;
		}

		SOC_INT32 alloc_threadID = ExtractThreadID(ptr);
		if (alloc_threadID != m_threadID)
		{
			ref_ThreadID = alloc_threadID;
			return false;
		}

		// note : this mean is the wrong access
		char memOP = ExtractMemOP(ptr);
		if ((memOP & MEM_POSTFREE_BIT) != 0)
		{
            GarbageCollect();
			// perform to GarbageCollecter
			// crash
			return true;
		}

		FreeInternal(ptr);
		return true;
	}

	//this free func is usable in other threads.
	void Allocator::PostponeFree(void* ptr)
	{
		if (m_threadID != ExtractThreadID(ptr))
		{
			// thread info is not same
			return;
		}

		SetMemOP(ptr, MEM_POSTFREE_BIT);
		m_postFreeQueue.Push(ptr);
	}

	bool Allocator::GarbageCollect()
	{
		void* ptr = nullptr;
		while ((ptr = m_postFreeQueue.Pop(nullptr)) != nullptr)
		{
			FreeInternal(ptr);
		}

		return true;
	}

	void Allocator::FreeInternal(void* ptr)
	{
		SOC_SIZE_T realSize = ExtractRealSize(ptr);
		SOC_INT32 alloc_threadID = ExtractThreadID(ptr);

		if (m_threadID != alloc_threadID)
		{
			// other thread's memory is can not free in here.
			// need to crash.
			return;
		}

		if (OVERFLOWCHECK_SUB(m_allocedMemoryRealSize, realSize))
		{
			// loging and crash
			return;
		}

		m_allocedMemoryRealSize -= realSize;
		void* pMem = GetRealMemory(ptr);
		CSlab* pSlab = GetSlab(realSize);

		if (pSlab != nullptr)
		{
			pSlab->PutMemory(pMem);
		}
		else
		{
			free(pMem);
		}
	}

	void* Allocator::CheckAlloc(void* ptr)
	{
		SOC_INT32 threadID = ExtractThreadID(ptr);
		if (threadID >= m_threadMax)
		{
			//error. loging and need to crash
			return nullptr;
		}

		if (*(char*)ptr != FREE_PATTERN)
		{
			//error. loging and need to crash
			return nullptr;
		}

		return ptr;
	}

	CSlab* Allocator::GetSlab(SOC_SIZE_T requiredSize)
	{
		int poolIndex = 0;

		SOC_SIZE_T requiredSizeTemp = requiredSize -1;
		while (true) // detecting the alignment.
		{
			if ( (requiredSizeTemp >> (poolIndex + m_minAlign)) == 0) 
				break;

			++poolIndex;
		}

		if (poolIndex >= m_alignCount)
			return nullptr;

		if (requiredSize > m_ppFreeListArray[poolIndex]->GetClassSize())
		{
			// wrong slab return
			//crash
			return nullptr;
		}

		return m_ppFreeListArray[poolIndex];
	}

	SOC_INT32 Allocator::ExtractThreadID(void* ptr)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -2;
		SOC_INT32 threadID = (*pMem & THREAD_MASK) >> THREAD_SHIFT;

		return threadID;
	}

	SOC_SIZE_T Allocator::ExtractSize(void* ptr)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -2;
		SOC_SIZE_T size = (*pMem & SIZE_MASK);

		return size;
	}

	SOC_SIZE_T Allocator::ExtractRealSize(void* ptr)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -2;
		SOC_SIZE_T size = (*pMem & SIZE_MASK) + 4 * 2;

		return size;
	}

	SOC_INT32 Allocator::ExtractTag(void* ptr)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -2;
		return *(pMem +1) & TAG_MASK;
	}

	char Allocator::ExtractMemOP(void* ptr)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -1;
		return (char)( (*pMem & MEMORY_MASK) >> MEMORY_SHIFT );
	}

	void Allocator::SetMemOP(void* ptr, char op)
	{
		SOC_INT32* pMem = (SOC_INT32*)ptr -1;
		*pMem = *pMem | (op << MEMORY_SHIFT);
	}
}