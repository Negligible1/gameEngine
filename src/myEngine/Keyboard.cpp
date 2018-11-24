#include "Keyboard.h"

namespace myengine
{

	Keyboard::Keyboard()
	{
		W = false;
		A = false;
		S = false;
		D = false;
		Shift = false;
		Space = false;
		Esc = false;
		ArrowUp = false;
		ArrowDown = false;
		ArrowLeft = false;
		ArrowRight = false;
	}

	Keyboard::~Keyboard()
	{

	}

	void Keyboard::keyChange(SDL_Event keyEvent)
	{
		//using the sdlevent we navigate a switch statement to find out which key "evented"
		//we then adjust the key based on the event type
		switch (keyEvent.key.keysym.sym)
		{

		case SDLK_w:
		{
			//If the event type is key up we set the key bool to false
			if (keyEvent.type == SDL_KEYUP)
			{
				W = false;
			}
			//otherwise it HAS to be a keydown, because only in those two situations will this function be called, so we set the key bool to true
			else
			{
				W = true;
			}
			break;
		}

		case SDLK_a:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				A = false;
			}
			else
			{
				A = true;
			}
			break;
		}

		case SDLK_s:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				S = false;
			}
			else
			{
				S = true;
			}
			break;
		}

		case SDLK_d:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				D = false;
			}
			else
			{
				D = true;
			}
			break;
		}

		case SDLK_LSHIFT:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				Shift = false;
			}
			else
			{
				Shift = true;
			}
			break;
		}

		case SDLK_SPACE:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				Space = false;
			}
			else
			{
				Space = true;
			}
			break;
		}

		case SDLK_ESCAPE:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				Esc = false;
			}
			else
			{
				Esc = true;
			}
			break;
		}

		case SDLK_UP:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				ArrowUp = false;
			}
			else
			{
				ArrowUp = true;
			}
			break;
		}

		case SDLK_DOWN:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				ArrowDown = false;
			}
			else
			{
				ArrowDown = true;
			}
			break;
		}

		case SDLK_LEFT:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				ArrowLeft = false;
			}
			else
			{
				ArrowLeft = true;
			}
			break;
		}

		case SDLK_RIGHT:
		{
			if (keyEvent.type == SDL_KEYUP)
			{
				ArrowRight = false;
			}
			else
			{
				ArrowRight = true;
			}
			break;
		}

		default:
		{
			break;
		}

		}
	}		
}