#include "Chip8_Core.h"
#include "Globals.h"
#include <SDL3/SDL_timer.h>

enum class MainStates
{
	Continue,
	Exit
};

int main()
{
	//TODO: Initialize things
	Chip8_Core chip8;

	uint64_t timer = SDL_GetTicks();
	MainStates state = MainStates::Continue;

	while (state == MainStates::Continue)
	{
		//TODO: Main loop
		uint64_t elapsedTime = SDL_GetTicks() - timer;
		if (elapsedTime >= 16)
		{
			// TODO Get this out of here, manage timer inside
			switch (chip8.Update())
			{
			case (Globals::UpdateStatus::Exit):
				state = MainStates::Exit;
				break;

			}
			timer = SDL_GetTicks();
		}
	}

	return 0;
}