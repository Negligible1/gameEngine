#include "Component.h"
#include "Entity.h"

namespace myengine
{
	Component::~Component()
	{

	}

	//Dummy definitions for virtual functions
	void Component::Initialise()
	{

	}
	void Component::Start()
	{

	}
	void Component::Update()
	{

	}
	void Component::Draw()
	{

	}

	std::shared_ptr<Entity> Component::getParentEntity()
	{
		//returns a shared pointer to the parent entity
		return parentEntity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		//returns a shared pointer to the core, obtain via the parent entity
		return getParentEntity()->getCore();
	}
}