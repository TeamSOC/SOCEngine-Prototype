#pragma once

namespace Memory {

	#define FREE_PATTERN 0xC

	/*
	if using much more memory, the form will be.. 
	have very long memory block. :)
	*/
	class CSlab
	{
	public:
		CSlab(size_t classSize, size_t bufferSize);
		~CSlab();

		void* GetMemory();
		void PutMemory(void* ptr);
		int GetClassSize() { return m_classSize; }
		int GetAllocatedMemorySize() { return m_allocatedMemoryBytes; }
		int GetAllMemorySize() { return m_bufferSize; }

	private:
		char* CreateMemory();

	private:
		size_t m_classSize;
		size_t m_bufferSize;
		size_t m_totalMemoryBytes;
		size_t m_allocatedMemoryBytes;
		char* m_pFree;
		char* m_pCache;

		std::vector<void*> m_vMemory;
	};
}