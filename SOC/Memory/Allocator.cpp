#include "../pch/pch.h"


namespace Memory {

	Allocator::Allocator(int threadID, int threadMax, int minAlign, int maxAlign, int bufferSize)
		: m_threadID(threadID)
		, m_threadMax(threadMax)
		, m_minAlign(minAlign)
		, m_maxAlign(maxAlign)
		, m_allocedMemoryRealSize(0)
		, m_lowWaterMark(std::numeric_limits<unsigned int>::max())
	{
		// for instance.. number of between 3 and 10 is not [10 - 3 = 7]. 
		// that is 8.
		m_alignCount = maxAlign - minAlign +1;
		
		m_ppFreeListArray = (CSlab**)malloc(m_alignCount * sizeof(CSlab*));
		for (int i=0; i<m_alignCount; ++i)
		{
			int memorySize = 1 << (i + minAlign);
			m_ppFreeListArray[i] = new CSlab(memorySize, bufferSize);
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

		free(m_ppFreeListArray);
	}

	void* Allocator::Alloc(size_t size, int tag)
	{
		// note : (thread | size) + tag
		int realSize = size + sizeof(int) * 2;

		if (OVERFLOWCHECK_ADD(m_allocedMemoryRealSize, realSize))
		{
			return nullptr;
		}

		CSlab* pSlab = GetSlab(realSize);
		m_allocedMemoryRealSize += realSize;

		unsigned int* pMem = nullptr;
		if (pSlab != nullptr)
		{
			pMem = (unsigned int*)pSlab->GetMemory();
		}
		else
		{
			pMem = (unsigned int*)malloc(realSize);
			memset(pMem, FREE_PATTERN, realSize);
		}

		if (pMem == nullptr)
		{
			// memory alloc failed. this is error.
			throw std::bad_alloc();
			return nullptr;
		}

		// max allocatable : 16777216 byte. 
		// this is 2^24 : 3 byte.
		// this form is [threadID | size][tag][we use byte]
		*pMem = ((m_threadID << THREAD_SHIFT) | size);
		*(pMem +1) = tag & TAG_MASK;

		return CheckAlloc(pMem +2);
	}

	bool Allocator::Free(void* ptr, int tag, int& threadID)
	{
		// all free to delayed object in here.

		if (tag != ExtractTag(ptr))
		{
			// note : not matched memory tag
			// tag info have to same
			// crash
			return false;
		}

		int alloc_threadID = ExtractThreadID(ptr);
		if (alloc_threadID != m_threadID)
		{
			threadID = alloc_threadID;
			return false;
		}

		// note : this mean is the wrong access
		char memOP = GetMemOP(ptr);
		if ((memOP & MEM_POSTFREE_BIT) != 0)
		{
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
		// this is not implemented yet.
	}

	bool Allocator::GarbageCollect()
	{
		// this is not implemented yet.
		return false;
	}

	void Allocator::FreeInternal(void* ptr)
	{
		int realSize = ExtractRealSize(ptr);
		int alloc_threadID = ExtractThreadID(ptr);

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
		unsigned int* pMem = GetRealMemory(ptr);
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
		int threadID = ExtractThreadID(ptr);
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

	CSlab* Allocator::GetSlab( int requiredSize )
	{
		int poolIndex = 0;

		int requiredSizeTemp = requiredSize -1;
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

	int Allocator::ExtractThreadID(void* ptr)
	{
		unsigned int* pMem = (unsigned int*)ptr -2;
		int threadID = (*pMem & THREAD_MASK) >> THREAD_SHIFT;

		return threadID;
	}

	int Allocator::ExtractSize(void* ptr)
	{
		unsigned int* pMem = (unsigned int*)ptr -2;
		size_t size = (*pMem & SIZE_MASK);

		return size;
	}

	int Allocator::ExtractRealSize(void* ptr)
	{
		unsigned int* pMem = (unsigned int*)ptr -2;
		size_t size = (*pMem & SIZE_MASK) + sizeof(int) *2;

		return size;
	}

	int Allocator::ExtractTag(void* ptr)
	{
		unsigned int* pMem = (unsigned int*)ptr -2;
		return *(pMem +1) & TAG_MASK;
	}

	char Allocator::GetMemOP(void* ptr)
	{
		unsigned int* pMem = (unsigned int*)ptr -2;
		return (char)( (*(pMem +1) & MEMORY_MASK) >> MEMORY_SHIFT );
	}

	void Allocator::SetMemOP(void* ptr, char op)
	{
		unsigned int* pMem = (unsigned int*)ptr -1;
		*pMem = *pMem | (op << MEMORY_SHIFT);
	}
}