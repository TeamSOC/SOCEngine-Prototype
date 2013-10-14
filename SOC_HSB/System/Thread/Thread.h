//
//  Thread.h
//  Created by SungBin_Hong on 13. 10. 13..
//  Copyright (c) 2013 years Teraphonia. All rights reserved.
//

#pragma once

namespace SOC_System {
	namespace Thread {

#ifndef TEST_STDCALL

#if defined(_WIN32) || defined(_WIN64)
#define TEST_STDCALL __stdcall
#define THREAD_LOCAL_VARIABLE __declspec(thread)

#else
#define TEST_STDCALL
#define THREAD_LOCAL_VARIABLE __thread

#endif
#endif
		
	class Thread
	{
	protected:
		SOC_HANDLE		m_handle;
		SOC_INT32		m_id;

	public:
		Thread(bool bCreate);
		virtual ~Thread();

		void	Resume();
		void	Stop();
		void	Join();
		void	Destroy();

		SOC_HANDLE GetHandle() { return m_handle; }
		void SetID(SOC_INT32 threadID);
		SOC_INT32 GetID() { return m_id; }
		void Exit() { m_bExited = true; }
		void ExitSign() { m_exitSign = false; }
		bool IsExited() { return m_bExited; }
		bool GetExitSign() { return m_exitSign; }

		virtual void Clean() {}

		static Thread* GetCurrent();

	private:
		void Create();
		void Attach();
		static SOC_ULONG TEST_STDCALL HandleFunc(void* pData);

	protected:
		virtual void CallBack(Thread* pCurThread) = 0;

	private:
		bool m_exitSign;
		bool m_bExited;

		static THREAD_LOCAL_VARIABLE Thread* g_pthreadInstance;
	};

	SOC_INT32 GetCurrentThreadID();
}
}