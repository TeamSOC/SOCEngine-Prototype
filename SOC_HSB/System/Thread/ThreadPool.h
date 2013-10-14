#pragma once

namespace SOC_System {
	namespace Thread {

	class ThreadPool 
		: public Thread
		, public Singleton<ThreadPool>
	{
	public:
		typedef	void (*PFUNCTION)(Thread* pCurThread);

	public:
		ThreadPool() 
			: Thread(false)
			, m_threadMax(0)
		{}
		virtual ~ThreadPool() 
		{}

		void CreateThreadPool(int n)
		{
			m_threadMax = n;

			if (m_threadMax == 0)
			{
				int coreCount = 0;
#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	coreCount = sinfo.dwNumberOfProcessors;
#else
	// mac os
	coreCount = (int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
			}

			//Loging
		}

		void Insert(PFUNCTION subLoop);
		void Excute(PFUNCTION mainLoop);
		bool Destroy();
		int GetThreadMax() { return m_threadMax; }

	private:
		void CallBack(Thread* pCurThread) {}

	private:
		class Worker : public Thread
		{
		public:
			Worker(PFUNCTION pFunction)
			: Thread(true)
			, m_function(pFunction)
			{}
			virtual ~Worker() 
			{}

			void CallBack(Thread* pCurThread)
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