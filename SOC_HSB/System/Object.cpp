#include "../pch/pch.h"

namespace SOC_System {

SOC_LONG Object::AddRef()
{
	if (m_count > 0)
	{
		++m_count;
	}
	else
	{
		//crash
	}

	return m_count;
}

SOC_LONG Object::AddRef(SOC_LONG value)
{
	if (m_count > 0)
	{
		m_count += value;
	}
	else
	{
		//crash
	}

	return m_count;
}

SOC_LONG Object::Release()
{
	SOC_LONG count = --m_count;

	if (count == 0)
	{
		delete this;
	}
	else if (count < 0)
	{
		// over released.
		//crash
	}

	return count;
}

}