#pragma once

/*
	* This program's memory to maked Singleton
	* will be "Auto Release"
	* but if you do AddRef, you have to call Release() function to the count.
*/

namespace SOC_System {

template <typename TYPE>
class Singleton : public Object
{
public:
	static TYPE& GetInstance()
	{
		if (s_pInstance != nullptr)
		{
			return *s_pInstance;
		}

		static volatile SOC_LONG tvalue = 0;

		while (true)
		{
#if defined(_WIN64) || defined(_WIN32)
			if (InterlockedCompareExchange((SOC_ULONG*)&tvalue, 1, 0) == 0)
#else
//
#endif
			{
				break;
			}

#if defined(_WIN64) || defined(_WIN32)
			YieldProcessor();
#else
			//
#endif
		}

		if (s_pInstance == nullptr)
		{
			Init();
		}

		tvalue = 0;

		return *s_pInstance;
	}

protected:
	virtual ~Singleton() {}
	
	static void Init()
	{
		TYPE * pInst = new TYPE();
		s_pInstance = pInst;

		::atexit(&finalize);
	}

	static void finalize()
	{
		if (s_pInstance)
		{
			s_pInstance->Release();
		}
	}

protected:
	static TYPE* s_pInstance;
};

template <typename TYPE>
TYPE* Singleton<TYPE>::s_pInstance = nullptr;

}