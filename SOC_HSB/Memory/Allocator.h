//
//  Allocator.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

#include <map>

namespace SOC_Memory {

    #define THREAD_MASK		0xff000000  // 1byte
    #define MEMORY_MASK		0xff000000	// 1byte
    #define SIZE_MASK		0x00ffffff	// 3byte
    #define TAG_MASK		0x00ffffff	// 3byte
    #define MEM_POSTFREE_BIT	0x1
    
	const int THREAD_SHIFT  = 24;
	const int MEMORY_SHIFT	= 24;
	const int POSTFREE_MAX	= 1024;

	class Allocator
	{
	private:
		Allocator(const Allocator& rhs);
	public:
		Allocator(SOC_INT32 threadID, SOC_INT32 threadMax, SOC_INT32 minAlign,
                  SOC_INT32 maxAlign, SOC_SIZE_T bufferSize);
		~Allocator();

	public:
		void*	Alloc(SOC_SIZE_T size, SOC_INT32 tag);
		bool	Free(void* ptr, SOC_INT32 tag, SOC_INT32& ref_ThreadID);
		void	PostponeFree(void* ptr); // not yet.
		bool	GarbageCollect();
		long	GetAllocatedMemory() { return m_allocedMemoryRealSize; }
	private:
		CSlab*	GetSlab(SOC_SIZE_T requiredSize);
		void*	CheckAlloc(void* ptr);
		void	FreeInternal(void* ptr);
		SOC_INT32	ExtractThreadID(void* ptr);
		SOC_SIZE_T	ExtractSize(void* ptr);
		SOC_SIZE_T	ExtractRealSize(void* ptr);
		SOC_INT32	ExtractTag(void* ptr);
		char	ExtractMemOP(void* ptr);	// memory ∞¸∑√ ¡¯«‡µø¿€¿ª «•Ω√(µπˆ±ÎøÎ)
		void	SetMemOP(void* ptr, char op);
		void*   GetRealMemory(void* ptr) { return (void*)((SOC_INT32*)ptr -2); }
		void*   GetMemory(void* ptr) { return (void*)((SOC_INT32*)ptr); }

	private:
		SOC_INT32 m_threadID;
		SOC_INT32 m_threadMax;
		SOC_INT32 m_alignCount;
		SOC_INT32 m_minAlign;
		SOC_INT32 m_maxAlign;
		SOC_SIZE_T m_allocedMemoryRealSize;
		SOC_INT32 m_lowWaterMark;
		CSlab** m_ppFreeListArray;

		SOC_System::MWSRQueue<void, POSTFREE_MAX> m_postFreeQueue;
	};
}