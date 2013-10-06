#pragma once

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
			if (InterlockedCompareExchange(&tvalue, 1, 0) == 0)
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
			if (s_pInstance == nullptr)
			{
				initialize();
			}

			tvalue = 0;

			return *s_pInstance;
		}
	}

protected:
	static TYPE* s_pInstance;
};

template <typename TYPE>
TYPE* Singleton<TYPE>::s_pInstance = nullptr;

}