#pragma once

#include <map>

namespace Memory {

#define THREAD_MASK			0xff000000  // 1byte
#define MEMORY_MASK			0xff000000	// 1byte
#define SIZE_MASK			0x00ffffff	// 3byte
#define TAG_MASK			0x00ffffff	// 3byte
#define MEM_POSTFREE_BIT	0x1

	const int THREAD_SHIFT	= 24;
	const int MEMORY_SHIFT	= 24;
	const int POSTFREE_MAX	= 1024;

	class Allocator
	{
	private:
		Allocator(const Allocator& rhs);
	public:
		Allocator(int threadID, int threadMax, int minAlign, int maxAlign, int bufferSize);
		~Allocator();

	public:
		void*	Alloc(size_t size, int tag);
		bool	Free(void* ptr, int tag, int& threadID);
		void	PostponeFree(void* ptr); // not yet.
		bool	GarbageCollect();
		long	GetAllocatedMemory() { return m_allocedMemoryRealSize; }
	private:
		CSlab*	GetSlab(int classSize);
		void*	CheckAlloc(void* ptr);
		void	FreeInternal(void* ptr);
		int		ExtractThreadID(void* ptr);
		int		ExtractSize(void* ptr);
		int		ExtractRealSize(void* ptr);
		int		ExtractTag(void* ptr);
		char	ExtractMemOP(void* ptr);	// memory 관련 진행동작을 표시(디버깅용)
		void	SetMemOP(void* ptr, char op);
		unsigned int* GetRealMemory(void* ptr) { return (unsigned int*)ptr -2; }
		unsigned int* GetMemory(void* ptr) { return (unsigned int*)ptr; }

	private:
		size_t m_lowWaterMark;
		int m_threadID;
		int m_threadMax;
		int m_alignCount;
		int m_minAlign;
		int m_maxAlign;
		size_t m_allocedMemoryRealSize;
		CSlab** m_ppFreeListArray;

		System::MWSRQueue<void, POSTFREE_MAX> m_postFreeQueue;
	};
}