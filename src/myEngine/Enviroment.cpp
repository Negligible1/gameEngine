#include "Enviroment.h"

namespace myengine
{

	Enviroment::Enviroment()
	{
		lastTime = SDL_GetTicks();
		FPS = 0;
		FPSCounter = 0;
		deltaTimeS = 0.0f;
		counterS = 0.0f;
	}

	Enviroment::~Enviroment()
	{

	}

	void Enviroment::Update()
	{
		unsigned int current = SDL_GetTicks();
		deltaTimeS = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		//FPS counter, once counterS is over 1 second long we set our FPS variable to be equal to the number of times this code has iterated
		if (counterS >= 1.0f)
		{
			FPS = FPSCounter;
			FPSCounter = 0;
			counterS = 0.0f;
		}

		counterS += deltaTimeS;
		++FPSCounter;

		// Limiter in case we're running really quick
		if (deltaTimeS < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTimeS)*1000.0f));
		}
	}
}