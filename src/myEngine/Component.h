#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

namespace myengine
{
	class Entity;
	class Core;

	class Component
	{
		friend class Entity;

	public:
		virtual ~Component();

		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getParentEntity();

	private:
		std::weak_ptr<Entity> parentEntity;
		bool started;

		virtual void Initialise();
		virtual void Start();
		virtual void Update();
		virtual void Draw();
	};
}



#endif // !MYENGINE_COMPONENT_H