#pragma once

#include <vector>
#include <string>

template <class Object>
class Container
{
protected:
	int order;
	std::vector<Object*> objects;

public:
	std::string name;
	std::string tag;
	std::string layer;

public:
	Container(void)
	{
		order = 0;
	}

	~Container(void)
	{
	}


private:
	enum FIND_ENUM{FIND_ENUM_NAME, FIND_ENUM_TAG};
	std::vector<Object*> _FindObject(std::string str, FIND_ENUM e, bool one)
	{
		std::vector<Object*> v;
		std::vector<Object*>::iterator iter;

		for(iter = objects.begin(); iter != objects.end(); ++iter)
		{
			string *findItem = e == FIND_ENUM_NAME ? &(*iter)->name : &(*iter)->tag;
			if( (*findItem) == str )
			{
				v.push_back((*iter));
				if(one) return v;
			}
		}
		return v;
	}

public:
	std::vector<Object*> FindObjects(std::string name)
	{
		return _FindObject(name, FIND_ENUM_NAME, false);
	}

	std::vector<Object*> FindObjectsWithTag(std::string tag)
	{
		return _FindObject(name, FIND_ENUM_TAG, false);
	}

	Object* FindObject(std::string name)
	{
		vector<Object*> v = _FindObject(name, FIND_ENUM_NAME, true);
		return v.size() == 0 ? NULL : v[0];
	}

	Object* FindObjectWithTag(std::string tag)
	{
		vector<Object*> v = _FindObject(tag, FIND_ENUM_TAG, true);
		return v.size() == 0 ? NULL : v[0];
	}

	Object* AddObject(Object *child, bool copy = false)
	{
		if(order > 0)
		{
			Object *c = copy == false ? child : new Object(*child);

			vector<Object*>::iterator iter;

			for(iter = objects.begin(); iter != objects.end(); ++iter)
			{
				if( (*iter)->order <= order )
				{
					c->order = (*iter)->order == order ? order + 1 : order;
					objects.insert(iter + 1, c);
					return c;
				}
			}
		}
		return nullptr;
	}

	Object* AddObject(Object *child, int order, bool copy = false)
	{
		Object *c = copy == false ? child : new Object(*child);

		c->order = (*(objects.end() - 1))->order + 1;
		objects.push_back(c);
		return c;
	}

	void DeleteObject(Object *child, bool remove)
	{
		vector<Object*>::iterator iter;

		for(iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if((*iter) == child)
			{
				if(remove)
					Utility::SAFE_DELETE(*iter);

				objects.erase(iter);
				return;
			}
		}

	}

	void DeleteAllObjects(bool remove)
	{
		if(remove)
		{
			for(vector<Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
				Utility::SAFE_DELETE(*iter);
		}

		objects.clear();
	}

public:
	int GetObjectsCount()
	{
		return objects.size();
	}

	Object* GetObject(int index)
	{
		return *(objects.begin()+index); 
	}

	static Object* Copy()
	{
		Object *obj = new Object();
		*obj = *this;

		return obj;
	}
};

