#include "../pch/pch.h"

int main()
{
	/////////////////////////////////////////////////////////////
	// MemoryPool Test
	SOC_Memory::MEMORYPOOL().Init(1);
	int* pArr = (int*)SOC_Memory::MEMORYPOOL().Alloc( sizeof(int) * 4 );
	
	for (int i=0; i<4; ++i)
		pArr[i] = i;

	for (int i=0; i<4; ++i)
		printf("%d\n", pArr[i]);

	SOC_Memory::MEMORYPOOL().Free((void*)pArr);
	/////////////////////////////////////////////////////////////

	return 0;
}