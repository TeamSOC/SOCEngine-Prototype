#pragma once

namespace SOC_System {

	class Object
	{
	public:
		Object() : m_count(1) 
		{}
		explicit Object(SOC_LONG count) : m_count(count)
		{}
		virtual ~Object() {}

		SOC_LONG AddRef();
		SOC_LONG AddRef(SOC_LONG value);
		SOC_LONG Release();

	private:
		Counter m_count;
	};
}