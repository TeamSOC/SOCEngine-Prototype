#pragma once

namespace Lock {

	// 'I' mean is interface
	class ILock
	{
	public:
		ILock() {}
		virtual ~ILock() {}
		
		virtual void Enter(const char* pFileName, int line) = 0;
		virtual void Leave() = 0;
		
		virtual void ReadLock(const char* pFileName, int line)
		{
			Enter(pFileName, line);
		}
		virtual void ReadUnlock()
		{
			Leave();
		}
		virtual void WriteLock(const char* pFileName, int line)
		{
			Enter(pFileName, line);			
		}
		virtual void WriteUnlock()
		{
			Leave();
		}
	};

	class CriticalSectionLock : public ILock
	{
	public:
		CriticalSectionLock(unsigned int spinCount = 0);
		virtual ~CriticalSectionLock();

		virtual void Enter(const char* pFileName, int line);
		virtual void Leave();

	private:
#if defined(_WIN32) || defined(_WIN64)
		CRITICAL_SECTION m_key;
#else
		pthread_mutex_t m_key;
#endif
	};

	namespace Spin	{
//		class BackoffLock : public ILock
	}

	namespace Helper {
		class ScopedLock
		{
		private:
			ScopedLock& operator=(const ScopedLock &);
		public:
			ScopedLock(ILock& lock, const char* pFileName = nullptr, int line = 0) : m_lock(lock)
			{
				m_lock.Enter(pFileName, line);
			}
			~ScopedLock()
			{
				m_lock.Leave();
			}

		private:
			ILock& m_lock;
		};

		template<typename T>
		class TypedScopedLock
		{
		private:
			TypedScopedLock& operator=(const TypedScopedLock &);
		public:
			TypedScopedLock(T& lock, const char* pFileName = nullptr, int line = 0) : m_lock(lock)
			{
				m_lock.Enter(pFileName, line);
			}
			~TypedScopedLock()
			{
				m_lock.Leave();
			}

		private:
			T& m_lock;
		};
	}
}

#define TYPED_SCOPE_LOCK(lock) Lock::Helper::TypedScopedLock<Lock::CriticalSectionLock> __lock(lock, __FILE__, __LINE__)