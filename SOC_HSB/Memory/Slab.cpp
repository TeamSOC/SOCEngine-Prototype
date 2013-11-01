//
//  Slab.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#include "../pch/pch.h"

namespace SOC_Memory {

	CSlab::CSlab(SOC_SIZE_T classSize, SOC_SIZE_T bufferSize)
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
	SOC_INT, SOC_PINT is for 64 bit.

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

		SOC_SIZE_T allocSize = m_bufferSize * m_classSize;
		if (OVERFLOWCHECK_ADD(m_totalMemoryBytes, allocSize))
		{
			//crash
			return nullptr;
		}

		char* pMemory = (char*)malloc(allocSize);
		if (pMemory == nullptr)
		{
			//crash
			return nullptr;
		}

		memset(pMemory, FREE_PATTERN, allocSize);

		for (SOC_SIZE_T i=0; i<m_bufferSize; ++i)
		{
			char* ptr = pMemory + i * m_classSize;
			*(SOC_PINT)ptr = (SOC_INT)(ptr + m_classSize);
		}

		*(SOC_PINT)(pMemory + (m_bufferSize -1) * m_classSize) = (SOC_INT)nullptr;

		m_vMemory.push_back(pMemory);

		m_totalMemoryBytes += allocSize;
		return pMemory;
	}

/*
// Note :
æÓ¬˜«« m_bufferSize ∫Øºˆ∞° «ˆ¿Á Ω«¡¶∑Œ «“¥Áπﬁ¿ª ºˆ ¿÷¥¬ ∏ﬁ∏∏Æ¿« √—∑Æ¿ª ∂Ê«œπ«∑Œ.. 
m_allocatedMemoryBytes <= m_bufferSize ¿Ã¥Ÿ.
ø¿πˆ«√∑ŒøÏ∞° ∞…∏∞¥Ÿ∏È m_bufferSize∏¶ ¥√∏± ∂ß ∞…∏± ∞Õ¿Ãπ«∑Œ
if (m_pFree != nullptr) æ»ø°º≠ ∏ﬁ∏∏Æ ø¿πˆ«√∑ŒøÏ ∞ÀªÁ∏¶ «“ « ø‰¥¬ æ¯¿ª ∞Õ¿Ã¥Ÿ.

Ω«¡¶∑Œ ≈´ ∏ﬁ∏∏Æ∏¶ «“¥Á πﬁ¿∏∏È ±◊∞… ¥Ÿ Ω·æﬂ ¥ŸΩ√ ∏ﬁ∏∏Æ «“¥Á¿ª ¥ı «—¥Ÿ.
±◊∑∏±‚ ∂ßπÆø° ∫Œ«œ∞° ∞…∏Æ¥¬ ¿œ¿∫ æ¯¿ª ∞Õ¿Ã¥Ÿ.
*/
	void* CSlab::GetMemory()
	{
		if (m_pFree != nullptr)
		{
			// pop the element in 'memory block'
			char* pMemory = m_pFree;
			m_pFree = (char*)(*(SOC_PINT)m_pFree);
			
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

		*(SOC_PINT)ptr = (SOC_INT)m_pFree;
		m_pFree = (char*)ptr;

		m_allocatedMemoryBytes -= m_classSize;
	}
}