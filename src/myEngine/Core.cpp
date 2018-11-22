#include <MYENGINE/Core.h>
#include <myEngine/Entity.h>

#include <GL/glew.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace myengine
{

	std::shared_ptr<Core> Core::initialise()
	{
		//creates useable pointer to self, sets a bool to false, sets weakptr to self
		std::shared_ptr<Core> toCore = std::make_shared<Core>();
		toCore->running = false;
		toCore->self = toCore;

		//initialise sdl, throws exception if issue
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		//create SDL window ( "| SDL_WINDOW_OPENGL" makes it suitable for an OpenGL rendering context)
		toCore->window = SDL_CreateWindow("Game Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		//creates an OPENGL rendering context within the sdl window we made earlier
		if (!SDL_GL_CreateContext(toCore->window))
		{
			throw std::exception();
		}

		//initialises glew, throws exceptions if issue
		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		return toCore;
	}

	Core::~Core()
	{
	
	}

	void Core::run()
	{
		//set running bool to true
		running = true;

		//loop while running bool is true
		while (running)
		{
			//handles quitting
			SDL_Event event = { 0 };
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) //if the red x is hit
				{
					running = false;
				}
			}

			//iterate through and call update on all entities
			CoreUpdate();

			//clear screen
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//call draw on all entities
			CoreDraw();

			//swap the memory buffer with the screen buffer
			SDL_GL_SwapWindow(window);
		}

	}

	void Core::pause()
	{
		running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> toEntity = std::make_shared<Entity>();
		entities.push_back(toEntity);
		toEntity->self = toEntity;
		toEntity->core = self;

		return toEntity;
	}

	void Core::CoreDraw()
	{
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();	it != entities.end(); it++)
		{
			(*it)->EntityDraw();
		}
	}

	void Core::CoreUpdate()
	{
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();	it != entities.end(); it++)
		{
			(*it)->EntityUpdate();
		}
	}

}