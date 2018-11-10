#include "Component.h"

#include <memory>
#include <vector>

//repeated code
#define ADDCOMPONENT \
  std::shared_ptr<T> toSelf = std::make_shared<T>(); \
  toSelf->parentEntity = self; \
  toSelf->started = false; \
  components.push_back(toSelf);

namespace myengine
{
	class Core;

	class Entity
	{
		friend class Core;

	public:
		//Functions
		template <typename T>
		std::shared_ptr<T> getComponent();
	
		//Add component templates
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			ADDCOMPONENT
			toSelf->Initialise();
			return toSelf;
		}

		template <typename T, typename A>
		std::shared_ptr<T> addComponent(A a)
		{
			ADDCOMPONENT
			toSelf->Initialise(a);
			return toSelf;
		}

		template <typename T, typename A, typename B>
		std::shared_ptr<T> addComponent(A a, B b)
		{
			ADDCOMPONENT
			toSelf->Initialise(a, b);
			return toSelf;
		}

		template <typename T, typename A, typename B, typename C>
		std::shared_ptr<T> addComponent(A a, B b, C c)
		{
			ADDCOMPONENT
			toSelf->Initialise(a, b, c);
			return toSelf;
		}

		template <typename T, typename A, typename B, typename C, typename D>
		std::shared_ptr<T> addComponent(A a, B b, C c, D d)
		{
			ADDCOMPONENT
			toSelf->Initialise(a, b, c, d);
			return toSelf;
		}

		template <typename T, typename A, typename B, typename C, typename D, typename E>
		std::shared_ptr<T> addComponent(A a, B b, C c, D d, E e)
		{
			ADDCOMPONENT
			toSelf->Initialise(a, b, c, d, e);
			return toSelf;
		}

		std::shared_ptr<Core> getCore();

	private:
		//Functions
		void EntityUpdate();
		void EntityDraw();

		//Variables
		std::vector<std::shared_ptr<Component> > components;
		std::weak_ptr<Entity> self;
		std::weak_ptr<Core> core;
	};
}