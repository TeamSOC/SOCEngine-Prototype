#include "../pch/pch.h"

namespace SOC_System {

	void Counter::operator = (SOC_LONG Value)
	{
		while (true)
		{
			SOC_ULONG temp = m_count;
#if defined(_WIN64) || defined(_WIN32)
			if (InterlockedCompareExchange((SOC_ULONG*)&m_count, Value, temp) == temp)
#else
			// OSAtomic Exchange
			if ()
#endif
			{
				break;
			}
			else
			{
#if defined(_WIN64) || defined(_WIN32)
				YieldProcessor();
#else
				//mac
#endif
			}
		}
	}
}