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
������ m_bufferSize ������ ���� ������ �Ҵ���� �� �ִ� �޸��� �ѷ��� ���ϹǷ�.. 
m_allocatedMemoryBytes <= m_bufferSize �̴�.
�����÷ο찡 �ɸ��ٸ� m_bufferSize�� �ø� �� �ɸ� ���̹Ƿ�
if (m_pFree != nullptr) �ȿ��� �޸� �����÷ο� �˻縦 �� �ʿ�� ���� ���̴�.

������ ū �޸𸮸� �Ҵ� ������ �װ� �� ��� �ٽ� �޸� �Ҵ��� �� �Ѵ�.
�׷��� ������ ���ϰ� �ɸ��� ���� ���� ���̴�.
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