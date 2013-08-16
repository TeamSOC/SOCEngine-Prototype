#pragma once

#include "Utility.h"

namespace Utility
{
	template< class T >
	class SingleTon
	{
	private:
		static T* instance;
/*
	protected:
		SingleTon()	{}
		virtual ~SingleTon(){}
*/
	public:
		static T* GetInstance()
		{
			if(instance == NULL)
				instance = new T();

			return instance;
		}

		void DeleteSingleTon()
		{
			Utility::SAFE_DELETE(instance);
		}
	};

}