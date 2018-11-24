#ifndef MYENGINE_KEYBOARD_H
#define MYENGINE_KEYBOARD_H

#include <SDL2/SDL.h>
#include <string>

namespace myengine
{
	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();

		//Updates the state of the keys
		void keyChange(SDL_Event keyEvent);

		//Get functions
		bool GetW() { return W; }
		bool GetA() { return A; }
		bool GetS() { return S; }
		bool GetD() { return D; }

		bool GetShift() { return Shift; }
		bool GetSpace() { return Space; }
		bool GetEsc()   { return Esc; }

		bool GetArrowUp()    { return ArrowUp; }
		bool GetArrowDown()  { return ArrowDown; }
		bool GetArrowLeft()  { return ArrowLeft; }
		bool GetArrowRight() { return ArrowRight; }

	private:
		bool W, A, S, D, Shift, Space, Esc, ArrowUp, ArrowDown, ArrowLeft, ArrowRight;
	};
}

#endif // !MYENGINE_KEYBOARD_H