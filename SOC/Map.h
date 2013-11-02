#pragma once

#include <map>
#include <string>

template <class Object>
class Map
{
private:
	std::map<std::string, Object*> map;

public:
	Map(void)
	{

	}

	~Map(void)
	{
		DeleteAll();
	}

public:
	Object* Add(std::string key, Object* object)
	{
		std::map<std::string, Object*>::iterator iter = hash.find(key);

		if(iter != hash.end())
			return iter->second;

		hash.insert(SOCHashMap<std::string, Object*>::value_type(key, object));

		return object;
	}

	Object* Find(std::string key)
	{
		std::map<std::string, Object*>::iterator iter = hash.find(key);
		return iter == hash.end() ? nullptr : iter->second;
	}

	void Delete(std::string key)
	{
		std::map<std::string, Object*>::iterator iter = hash.find(key);

		if( iter == hash.end() )
			return;

		Utility::SAFE_DELETE(iter->second);

		hash.erase(iter);
	}

	void Delete(Object* object, bool dealloc)
	{
		std::map<std::string, Object*>::iterator iter;
		for(iter = hash.begin(); iter != hash.end(); ++iter)
		{
			if( (*iter).second == object )
			{
				if(dealloc)
					delete object;

				hash.erase(iter);
				return;
			}
		}
	}

	void DeleteAll()
	{
		for(std::map<std::string, Object*>::iterator iter = hash.begin();iter != hash.end(); ++iter)
			Utility::SAFE_DELETE(iter->second);

		hash.clear();
	}
};

