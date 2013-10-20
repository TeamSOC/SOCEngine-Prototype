#pragma once

namespace SOC_System {
	using namespace Lock;

	// need to Spin lock. current lock is slow.
class Counter
{
public:
	Counter() : m_count(0)
	{}
	Counter(SOC_LONG value) : m_count(value)
	{}
	virtual ~Counter() {}
	SOC_LONG Get() { return m_count; }

public:
	void operator = (SOC_LONG value);
    
	SOC_LONG operator ++ () // prefix ++
	{
#if defined(_WIN64) || defined(_WIN32)
		return InterlockedIncrement((SOC_ULONG*)&m_count);
#else
        return InterlockedIncrement(&m_count);
#endif
	}
	SOC_LONG operator ++ (int) // postfix ++
	{
#if defined(_WIN64) || defined(_WIN32)
		return InterlockedIncrement((SOC_ULONG*)&m_count) -1;
#else
		return InterlockedIncrement(&m_count) -1;
#endif
	}

	SOC_LONG operator -- ()
	{
#if defined(_WIN64) || defined(_WIN32)
		return InterlockedDecrement((SOC_ULONG*)&m_count);
#else
        return InterlockedDecrement(&m_count);
#endif
	}

	SOC_LONG operator -- (int)
	{
#if defined(_WIN64) || defined(_WIN32)
		return InterlockedDecrement((SOC_ULONG*)&m_count) +1;
#else
		return InterlockedDecrement(&m_count) +1;
#endif
	}

	void operator += (SOC_LONG value)
	{
#if defined(_WIN64) || defined(_WIN32)
		InterlockedExchangeAdd((SOC_ULONG*)&m_count, value);
#else
        InterlockedExchangeAdd(&m_count, value);
#endif
	}

	void operator -= (SOC_LONG value)
	{
#if defined(_WIN64) || defined(_WIN32)
		InterlockedExchangeSubtract((SOC_ULONG*)&m_count, value);
#else
        InterlockedExchangeSubtract(&m_count, value);
#endif
	}

	bool operator != (SOC_LONG value) const { return (m_count != value); }
	operator SOC_LONG () const { return m_count; }

private:
	SOC_LONG m_count;
};

}