#include "../pch/pch.h"

namespace Memory {
	CSlab::CSlab(size_t classSize, size_t bufferSize)
		: m_classSize(classSize)
		, m_bufferSize(bufferSize)
		, m_totalMemoryBytes(0)
		, m_allocatedMemoryBytes(0)
		, m_pFree(nullptr)
		, m_pCache(nullptr)
	{
	//	m_pFree = CreateMemory();
	}

	CSlab::~CSlab()
	{
		std::vector<void*>::iterator itr = m_vMemory.begin();
		for (; itr != m_vMemory.end(); ++itr)
		{
			free(*itr);
		}
		m_vMemory.clear();
	}

	/*
	Setting memory address position
	and saving the next address.
	INT_PTR, PINT_PTR is for 64 bit.

	if this setting is completed, the form is.. following.
	
	memory : [0][1][2][3][4][5][6][7][8][9]
	result : [1 address][2 address]...[9 address][0]
	*/
	char* CSlab::CreateMemory()
	{
		if (OVERFLOWCHECK_MUL(m_bufferSize, m_classSize))
		{
			//crash
			return nullptr;
		}

		size_t allocSize = m_bufferSize * m_classSize;
		if (OVERFLOWCHECK_ADD(m_totalMemoryBytes, allocSize))
		{
			//crash
			return nullptr;
		}

		char* pMemory = (char*)malloc(m_classSize * m_bufferSize);
		if (pMemory == nullptr)
		{
			//crash
			return nullptr;
		}

		memset(pMemory, FREE_PATTERN, m_bufferSize * m_classSize);

		for (size_t i=0; i<m_bufferSize; ++i)
		{
			char* ptr = pMemory + i*m_classSize;
			*(PINT_PTR)ptr = (INT_PTR)(ptr + m_classSize);
		}

		*(PINT_PTR)(pMemory + (m_bufferSize -1) * m_classSize) = (INT_PTR)nullptr;

		m_vMemory.push_back(pMemory);

		m_totalMemoryBytes += (m_bufferSize * m_classSize);
		return pMemory;
	}

/*			
어차피 m_bufferSize 변수가 현재 실제로 할당받을 수 있는 메모리의 총량을 뜻하므로.. 
m_allocatedMemoryBytes <= m_bufferSize 이다.
오버플로우가 걸린다면 m_bufferSize를 늘릴 때 걸릴 것이므로
if (m_pFree != nullptr) 안에서 메모리 오버플로우 검사를 할 필요는 없을 것이다.

실제로 큰 메모리를 할당 받으면 그걸 다 써야 다시 메모리 할당을 더 한다.
그렇기 때문에 부하가 걸리는 일은 없을 것이다.
*/
	void* CSlab::GetMemory()
	{
		if (m_pFree != nullptr)
		{
			// pop the element in 'memory block'
			char* pMemory = m_pFree;
			m_pFree = (char*)(*(PINT_PTR)m_pFree);
			
			m_allocatedMemoryBytes += m_classSize;
			return static_cast<void*>(pMemory);
		}
		else
		{
			if (OVERFLOWCHECK_ADD(m_bufferSize, m_bufferSize))
			{
				return nullptr;
			}

			m_pFree = CreateMemory();
			m_bufferSize += m_bufferSize;

			return GetMemory();
		}
	}

	void CSlab::PutMemory(void* ptr)
	{
		// too much free memory
		if (OVERFLOWCHECK_SUB(m_allocatedMemoryBytes, m_classSize))
		{
			// loging overflow
			// if the unsgined integer [x + 10] is overflowed, 
			// you can detect to overflowed memory is [x + 10] in 'ADD' operation.

			return;
		}

		memset(ptr, FREE_PATTERN, m_classSize);

		*(PINT_PTR)ptr = (INT_PTR)m_pFree;
		m_pFree = (char*)ptr;

		m_allocatedMemoryBytes -= m_classSize;
	}
}