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
#if defined(_WIN32) || defined(_WIN64)
		HANDLE			m_handle;
#else
		int				m_handle;
#endif
		SOC_INT32		m_id;

	public:
		Thread(bool bCreate);
		virtual ~Thread();

		void	Resume();
		void	Stop();
		void	Join();
		void	Destroy();

		HANDLE GetHandle() { return m_handle; }
		void SetID(SOC_INT32 threadID);
		SOC_INT32 GetID() { return m_id; }

		virtual void Clean() {}

		static Thread* GetCurrent();

	private:
		void Create();
		void Attach();
		static SOC_ULONG TEST_STDCALL HandleFunc(void* pData);

	protected:
		virtual void CallBack() = 0;

	private:
		static THREAD_LOCAL_VARIABLE Thread* g_pthreadInstance;
	};

	SOC_INT32 GetCurrentThreadID();
}
}