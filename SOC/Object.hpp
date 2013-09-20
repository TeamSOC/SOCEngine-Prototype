
namespace Rendering
{
	template<class ComponentType>
	ComponentType* Object::AddComponent()
	{
		ComponentType *compo = new ComponentType;

		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
		{
			if( (*iter)->ComponentType != Component::Type::User )
				return nullptr;
		}

		//오직 유저 컴포넌트만 중복 가능
		compo->Initialize();
		componenets.push_back(compo);
	}

	template<class ComponentType>
	ComponentType* Object::GetComponent()
	{
		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
		{
			if((*iter)->ComponentType == ComponentType::ComponentType)
				return (*iter);
		}

		return nullptr;
	}

	template<class ComponentType>
	std::vector<ComponentType*> Object::GetComponents()
	{
		std::vector<Component*> v;

		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
		{
			if((*iter)->ComponentType == ComponentType::ComponentType)
				v.push_back((*iter));
		}

		return v;
	}
}