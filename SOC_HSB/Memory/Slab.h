//
//  Slab.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

namespace SOC_Memory {

	#define FREE_PATTERN 0xC

	/*
	if using much more memory, the form will be.. 
	have very long memory block. :)
	*/
	class CSlab
	{
	public:
		CSlab(SOC_SIZE_T classSize, SOC_SIZE_T bufferSize);
		~CSlab();

		void* GetMemory();
		void PutMemory(void* ptr);
		SOC_SIZE_T GetClassSize() { return m_classSize; }
		SOC_SIZE_T GetAllocatedMemorySize() { return m_allocatedMemoryBytes; }
		SOC_SIZE_T GetAllMemorySize() { return m_bufferSize; }

	private:
		char* CreateMemory();

	private:
		SOC_SIZE_T m_classSize;
		SOC_SIZE_T m_bufferSize;
		SOC_SIZE_T m_totalMemoryBytes;
		SOC_SIZE_T m_allocatedMemoryBytes;
		char* m_pFree;
		char* m_pCache;

		std::vector<void*> m_vMemory;
	};

}