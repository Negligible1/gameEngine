#include "Entity.h"

namespace myengine
{

	template <typename T>
	std::shared_ptr<T> Entity::getComponent()
	{

	}




	std::shared_ptr<Core> Entity::getCore()
	{
		//lock lets us obtain a shared_ptr from a weak_ptr(?)
		return core.lock();
	}

	void Entity::EntityUpdate()
	{
		//iterate through all components belonging to this entity and run update on them
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin(); it != components.end(); it++)
		{
			//if the entity has not yet "started" call Start function and set started bool to true
			if (!(*it)->started)
			{
				(*it)->Start();
				(*it)->started = true;
			}

			//then update
			(*it)->Update();
		}

	}

	void Entity::EntityDraw()
	{
		//iterate through all components belonging to this entity and draw them
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin(); it != components.end(); it++)
		{
			(*it)->Draw();
		}
	}

}