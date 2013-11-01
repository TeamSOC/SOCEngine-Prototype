#pragma once

namespace SOC_System {
	namespace Thread {

	class ThreadPool 
		: public SOCThread
		, public Singleton<ThreadPool>
	{
	public:
		typedef	void (*PFUNCTION)(SOCThread* pCurThread);

	public:
		ThreadPool() 
			: SOCThread(false)
			, m_threadMax(0)
		{}
		virtual ~ThreadPool() 
		{}

		void CreateThreadPool(int n)
		{
			m_threadMax = n;

			if (m_threadMax == 0)
			{
#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	m_threadMax = sinfo.dwNumberOfProcessors;
#else
	// mac os
	m_threadMax = (int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
			}

			//Loging
		}

		void Insert(PFUNCTION subLoop);
		void Excute(PFUNCTION mainLoop);
		bool Destroy();
		int GetThreadMax() { return m_threadMax; }

	private:
		void CallBack(SOCThread* pCurThread) {}

	private:
		class Worker : public SOCThread
		{
		public:
			Worker(PFUNCTION pFunction)
			: SOCThread(true)
			, m_function(pFunction)
			{}
			virtual ~Worker() 
			{}

			void CallBack(SOCThread* pCurThread)
			{
				m_function(pCurThread);
			}

		private:
			PFUNCTION m_function;
		};

	private:
		typedef	std::vector<Worker*> VECTOR;

		VECTOR m_workers;
		long m_ThreadNum;
		int m_threadMax;
	};

}
}