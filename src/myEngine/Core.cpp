#include "Core.h"
#include <myEngine/Entity.h>

#include <GL/glew.h>
#include <iostream>

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

		toCore->device = alcOpenDevice(NULL);

		if (!toCore->device)
		{
			throw std::exception();
		}

		toCore->context = alcCreateContext(toCore->device, NULL);

		if (!toCore->context)
		{
			alcCloseDevice(toCore->device);
			throw std::exception();
		}

		if (!alcMakeContextCurrent(toCore->context))
		{
			alcDestroyContext(toCore->context);
			alcCloseDevice(toCore->device);
			throw std::exception();
		}

		return toCore;
	}

	Core::~Core()
	{

	}

	void Core::run()
	{
		//Checks that all functionality has been initialised
		AdditionalInits();

		//set running bool to true
		running = true;

		//Turns on depth test so that triangle in front are always drawn in front, regardless of draw order
		glEnable(GL_DEPTH_TEST);

		//loop while running bool is true
		while (running)
		{
			//handles SDL events
			SDL_Event myEvent = { 0 };
			while (SDL_PollEvent(&myEvent))
			{
				if (myEvent.type == SDL_QUIT)
				{
					running = false;
				}
				else if (myEvent.type == SDL_KEYDOWN || myEvent.type == SDL_KEYUP)
				{
					keyboard->keyChange(myEvent);
				}
			}

			//Update our enviroment to get an accurate deltaTimeS
			enviroment->Update();

			//iterate through and call update on all entities
			CoreUpdate();

			//clear screen to the clear colour and clears the depth buffer
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//call draw on all entities
			CoreDraw();

			//swap the memory buffer with the screen buffer
			SDL_GL_SwapWindow(window);

			std::cout << "FPS: " << enviroment->getFPS() << std::endl;
		}
	}

	void Core::pause()
	{
		running = false;
	}

	void Core::AdditionalInits()
	{
		//If it hasn't been done already we'll initialise our keyboard and enviroment class here
		if (!keyboard)
		{
			keyboard = std::make_shared<Keyboard>();
		}
		if (!enviroment)
		{
			enviroment = std::make_shared<Enviroment>();
		}
		if (!collision)
		{
			collision = std::make_shared<Collision>();
		}
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		//Checks that all functionality has been initialised
		AdditionalInits();

		std::shared_ptr<Entity> toEntity = std::make_shared<Entity>();
		entities.push_back(toEntity);
		toEntity->self = toEntity;
		toEntity->core = self;

		return toEntity;
	}

	void Core::CoreDraw()
	{
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->EntityDraw();
		}
	}

	void Core::CoreUpdate()
	{
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->EntityUpdate();
		}
	}

}