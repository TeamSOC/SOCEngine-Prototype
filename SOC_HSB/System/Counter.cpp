#include "../pch/pch.h"

namespace SOC_System {

	void Counter::operator = (SOC_LONG Value)
	{
		static CriticalSectionLock lock;
		unsigned long temp = 0;
		/*
		while (true)
		{
			SOC_ULONG temp = m_count;

			{
				TYPED_SCOPE_LOCK(lock);
				temp = m_count;
				if (m_count == temp)
					m_count = Value;
			}

			//
		}

		*/
	}
}