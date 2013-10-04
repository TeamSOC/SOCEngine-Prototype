#include "../../pch/pch.h"

namespace Lock {

	CriticalSectionLock::CriticalSectionLock(unsigned int spinCount)
	{
#if defined(_WIN32) || defined(_WIN64)
	#if (_WIN32_WINNT >= 0x0600) // version >= vista.
		InitializeCriticalSectionEx(&m_key, spinCount, CRITICAL_SECTION_NO_DEBUG_INFO);
	#else
		InitializeCriticalSectionAndSpinCount(&m_key, spinCount);
	#endif
#else
        pthread_mutex_init(&m_key, nullptr);
#endif
	}

	CriticalSectionLock::~CriticalSectionLock()
	{
#if defined(_WIN32) || defined(_WIN64)
		DeleteCriticalSection(&m_key);
#else
        pthread_mutex_destroy(&m_key);
#endif
	}

	void CriticalSectionLock::Enter(const char* pFileName, int line)
	{
#if defined(_WIN32) || defined(_WIN64)
		EnterCriticalSection(&m_key);
#else
        pthread_mutex_lock(&m_key);
#endif
	}

	void CriticalSectionLock::Leave()
	{
#if defined(_WIN32) || defined(_WIN64)
		LeaveCriticalSection(&m_key);
#else
        pthread_mutex_unlock(&m_key);
#endif
	}
}