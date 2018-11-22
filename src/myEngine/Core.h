#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace myengine
{

	class Entity;
	class Camera;

	class Core
	{
	public:
		static std::shared_ptr<Core> initialise();
		~Core();

		void run();
		void pause();

		void setCamera(std::shared_ptr<Camera> cam) { currCamera = cam; }
		std::shared_ptr<Camera> getCamera() { return currCamera; }

		std::shared_ptr<Entity> addEntity();

	private:
		void CoreDraw();
		void CoreUpdate();

		bool running;
		std::vector<std::shared_ptr<Entity> > entities;
		std::weak_ptr<Core> self;

		std::shared_ptr<Camera> currCamera;

		SDL_Window *window;
	};
}