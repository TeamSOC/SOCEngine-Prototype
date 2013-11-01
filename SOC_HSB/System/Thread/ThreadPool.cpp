#include "../../pch/pch.h"

namespace SOC_System {
	namespace Thread {

	void ThreadPool::Insert(PFUNCTION subLoop)
	{
		static int threadID_Last = 1;

		Worker* pWorker = new Worker(subLoop);
		if (pWorker != nullptr)
		{
			pWorker->SetID(threadID_Last);
			++threadID_Last;

			m_workers.push_back(pWorker);
		}
	}

	void ThreadPool::Excute(PFUNCTION mainLoop)
	{
		if (m_threadMax == 0)
			this->CreateThreadPool(0);

		this->SetID(0); // mainThread ID : 0

		// Purform all sub thread.
		for (VECTOR::iterator itr=m_workers.begin(); itr != m_workers.end(); ++itr)
		{
			(*itr)->Resume();
		}

		// from here area of mainthread.

		mainLoop(this);

		Join();
		for (VECTOR::iterator itr=m_workers.begin(); itr != m_workers.end(); ++itr)
		{
			(*itr)->ExitSign();
		}

		// Each threads are have to release resource all.
		for (;;)
		{
			if (Destroy() == true)
				break;

#if defined(_WIN32) || defined(_WIN64)
			Sleep(100); // 0.1 sec. this is millisec.
#else
            usleep(100000); // 0.1 sec. this is microsec.
#endif
		}
	}

	bool ThreadPool::Destroy()
	{
		bool isAllExited = true;
		for (VECTOR::iterator itr=m_workers.begin(); itr != m_workers.end(); ++itr)
		{
			if ( (*itr) == nullptr)
				continue;
			if ( (*itr)->IsExited() == false)
			{
				isAllExited = false;
				continue;
			}

			SAFE_DELETE( (*itr) );
		}

		return isAllExited;
	}

}
}