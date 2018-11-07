#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace myengine
{

	class Entity;

	class Core
	{
	public:
		static std::shared_ptr<Core> initialise();
		~Core();

		void run();

	private:
		bool running;
		std::vector<std::shared_ptr<Entity> > entities;
		std::weak_ptr<Core> self;

		SDL_Window *window;
	};
}