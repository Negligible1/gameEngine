#ifndef MYENGINE_ENVIROMENT_H
#define MYENGINE_ENVIROMENT_H

#include <SDL2/SDL.h>

namespace myengine
{
	class Enviroment
	{
	public:
		Enviroment();
		~Enviroment();

		void Update();

		float getDeltaTimeS() { return deltaTimeS; }
		int getFPS() { return FPS; }

	private:
		float deltaTimeS;
		unsigned int lastTime;
		int FPS;
		int FPSCounter;
		float counterS;
	};
}
#endif // !MYENGINE_ENVIROMENT_H