//
//  Thread.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#include "../../pch/pch.h"

namespace SOC_System {
	namespace Thread {

Thread* Thread::GetCurrent()
{
	// thread local variable type
	return g_pthreadInstance;
}

SOC_INT32 GetCurrentThreadID()
{
	if (Thread::GetCurrent() == nullptr)
	{
		return 0;
	}

	return Thread::GetCurrent()->GetID();
}

Thread* Thread::g_pthreadInstance = nullptr;

Thread::Thread(bool bCreate)
	: m_handle(0)
	, m_id(0)
	, m_bExited(false)
	, m_exitSign(true)
{
	if (bCreate)
		Create();
	else
		Attach();
}

Thread::~Thread()
{
	if (m_handle != 0)
	{
#if defined(_WIN32) || defined(_WIN64)
		CloseHandle(m_handle);
#else

#endif
	}
}

SOC_ULONG Thread::HandleFunc(void* pData)
{
	if (pData != nullptr)
	{
		Thread* pThread = static_cast<Thread*>(pData);
		g_pthreadInstance = pThread;

		pThread->CallBack(pThread);

		if (pThread)
			pThread->Exit();
	}
	else
	{
		//Crash
	}

	return 0;
}

void Thread::SetID(SOC_INT32 threadID)
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

void Thread::Resume()
{	
#if defined(_WIN32) || defined(_WIN64)
	ResumeThread(m_handle);
#else
	//mac os
#endif
}

void Thread::Stop()
{
#if defined(_WIN32) || defined(_WIN64)
	SuspendThread(m_handle);
#else
	//mac os
#endif
}

void Thread::Join()
{
#if defined(_WIN32) || defined(_WIN64)
	WaitForSingleObject(m_handle, INFINITE);
#else
	//mac os
#endif
}

void Thread::Destroy()
{
#if defined(_WIN32) || defined(_WIN64)
	_endthreadex(0);
#else
	//mac os
#endif
}

void Thread::Create()
{
	SOC_UINT32 threadID = 0;

#if defined(_WIN32) || defined(_WIN64)
	m_handle = (HANDLE)_beginthreadex(nullptr, 
		0, &Thread::HandleFunc, this, CREATE_SUSPENDED, &threadID);

	if (m_handle == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		//loging and crash.
	}

#else
	//mac os
#endif
}

void Thread::Attach()
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

}
}