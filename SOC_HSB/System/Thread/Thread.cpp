//
//  Thread.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#include "../../pch/pch.h"



namespace SOC_System {
	namespace Thread {

THREAD_LOCAL_INITSIGN_VARIABLE SOCThread* SOCThread::g_pthreadInstance = nullptr;

SOC_INT32 GetCurrentThreadID()
{
    if (SOCThread::GetCurrent() == nullptr)
    {
        return 0;
    }
            
    return SOCThread::GetCurrent()->GetID();
}
        

SOCThread* SOCThread::GetCurrent()
{
	// thread local variable type
	return g_pthreadInstance;
}

SOCThread::SOCThread(bool bCreate)
	: m_handle(nullptr)
	, m_id(0)
	, m_bExited(false)
	, m_exitSign(true)
{
	if (bCreate)
		Create();
	else
		Attach();
}

SOCThread::~SOCThread()
        {
	if (m_handle != nullptr)
	{
#if defined(_WIN32) || defined(_WIN64)
		CloseHandle(m_handle);
#else
        pthread_detach(m_handle);
#endif
	}
}

void* SOCThread::HandleFunc(void* pData)
{
	if (pData != nullptr)
	{
		SOCThread* pThread = static_cast<SOCThread*>(pData);
		g_pthreadInstance = pThread;

		pThread->CallBack(pThread);

		if (pThread)
			pThread->Exit();
	}
	else
	{
		//Crash
	}
    
    return nullptr;
}

void SOCThread::SetID(SOC_INT32 threadID)
{
	m_id = threadID;

#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	SetThreadAffinityMask(m_handle, 1<< (m_id % sinfo.dwNumberOfProcessors));
#else
	// mac os
//	int numberOfCore = 0;
//	numberOfCore = sysconf(_SC_NPROCESSORS_ONLN);
//
#endif
}

//////////////////////////////
// not implemented in xcode
void SOCThread::Resume()
{	
#if defined(_WIN32) || defined(_WIN64)
	ResumeThread(m_handle);
#else
	//mac os
#endif
}

// not implemented in xcode
void SOCThread::Stop()
{
#if defined(_WIN32) || defined(_WIN64)
	SuspendThread(m_handle);
#else
	//mac os
#endif
}
//////////////////////////////
        
void SOCThread::Join()
{
#if defined(_WIN32) || defined(_WIN64)
	WaitForSingleObject(m_handle, INFINITE);
#else
	pthread_join(m_handle, nullptr);
#endif
}

void SOCThread::Destroy()
{
#if defined(_WIN32) || defined(_WIN64)
	_endthreadex(0);
#else
    pthread_exit(0);
#endif
}

void SOCThread::Create()
{
	SOC_INT32 threadID = 0;

#if defined(_WIN32) || defined(_WIN64)
	m_handle = (HANDLE)_beginthreadex(nullptr, 
		0, &SOCThread::HandleFunc, this, CREATE_SUSPENDED, &threadID);

	if (m_handle == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		//loging and crash.
	}

#else
    
    threadID = pthread_create(&m_handle, nullptr, SOCThread::HandleFunc, this);
    if (threadID < 0)
    {
        perror("[System] : Thread create error");
        //loging and crash
    }
#endif
}

////////////////////////////////////
//not implemented in xcode
void SOCThread::Attach()
{
#if defined(_WIN32) || defined(_WIN64)
	BOOL ret = DuplicateHandle(::GetCurrentProcess(), ::GetCurrentThread(), 
		::GetCurrentProcess(), &m_handle, DUPLICATE_SAME_ACCESS, false, 0);

	if (ret)
	{
		DWORD err = ::GetLastError();
		//loging and crash.
	}
#else
	//mac os
#endif

	g_pthreadInstance = this;
}
////////////////////////////////////

}
}