#include "../pch/pch.h"

namespace SOC_System {

	void Counter::operator = (SOC_LONG value)
	{
		while (true)
		{
			SOC_ULONG temp = m_count;
#if defined(_WIN64) || defined(_WIN32)
			if (InterlockedCompareExchange((SOC_ULONG*)&m_count, value, temp) == temp)
#else
			// OSAtomic Exchange
			if (InterlockedCompareExchange(&m_count, value, temp))
#endif
			{
				break;
			}
			else
			{
                //for hyper threading
//                YieldProcessor();
			}
		}
	}
}