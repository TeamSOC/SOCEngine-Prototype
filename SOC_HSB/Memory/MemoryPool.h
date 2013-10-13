//
//  MemoryPool.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

namespace SOC_Memory {
	using namespace SOC_System;
	using namespace SOC_System::Thread;

	// Default
	const int MIN_EXP = 3;
	const int MAX_EXP = 8;
	const int BUFFER_SIZE = 1024;

	template<int MinExp, int MaxExp, int BufferNum> 
	class MemoryPool : public Singleton< MemoryPool<MinExp, MaxExp, BufferNum> >
	{
	public:
		MemoryPool() : m_allocator(nullptr)
		{}
		virtual ~MemoryPool()
		{
			for (int i=0; i<m_threadCount; ++i)
			{
				if (m_allocator == nullptr)
					continue;

				delete m_allocator[i];
			}

			SAFE_FREE(m_allocator);
		}

		void Init(int threadCount)
		{
			m_threadCount = threadCount;
			m_allocator = (Allocator**)malloc( sizeof(Allocator*) * threadCount );

			if (m_allocator == nullptr) // bad alloc
			{
				//Crash
			}

			for (int i=0; i<m_threadCount; ++i)
			{
				m_allocator[i] = new Allocator(i, m_threadCount, MinExp, MaxExp, BufferNum);
			}
		}

		void* Alloc(SOC_SIZE_T size, SOC_INT32 tag = 0)
		{
			int thread = GetCurrentThreadID();
			return m_allocator[thread]->Alloc(size, tag);
		}

		void Free(void* ptr, SOC_INT32 tag = 0)
		{
			if (ptr == nullptr)
			{
				// Loging
				return;
			}

			int thread = GetCurrentThreadID();
			int allocated_threadID;
			if (m_allocator[thread]->Free(ptr, tag, allocated_threadID) == false)
			{
				if (allocated_threadID < m_threadCount)
				{
					m_allocator[allocated_threadID]->PostponeFree(ptr);
				}
				else
				{
					//Loging
					// crash
					return;
				}
			}
		}

		SOC_ULONG GetAllocatedMemory(int threadID)
		{
			if (threadID >= 0 && threadID < m_threadCount)
				return m_allocator[threadID]->GetAllocatedMemory();

			return 0;
		}

	private:
		int GetIndex_OfMemorySize(SOC_SIZE_T sizeToCheck)
		{
			unsigned int index = 0;
			
			while (true)
			{
				// +8 is.. tag. need to taging to memory
				if ( ((sizeToCheck + 8) -1) >> (index + MinExp) == 0)
					break;

				++index;
			}

			return index;
		}

	private:
		Allocator** m_allocator;
		int m_threadCount;
	};

	static MemoryPool<MIN_EXP, MAX_EXP, BUFFER_SIZE>& MEMORYPOOL()
	{
		return MemoryPool<MIN_EXP, MAX_EXP, BUFFER_SIZE>::GetInstance();
	}
};