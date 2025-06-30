#include "Chip8.h"
#include "Globals.h"

#include <SDL3/SDL_timer.h>
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

constexpr float LoopRate = 0.8f;

enum class MainStates
{
	Continue,
	Exit
};

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "[ERROR] You must enter the name of the rom to execute" << std::endl;
		return 0;
	}
	else if (argc > 2)
	{
		std::cout << "[ERROR] Too many arguments" << std::endl;
		return 0;
	}
	Chip8 chip8;

	uint64_t timer = SDL_GetTicks();
	MainStates state = MainStates::Continue;

	uint64_t lastTick = 0;
	uint64_t freq = SDL_GetPerformanceFrequency();;
	float preciseTimer = 0;

	if (!chip8.LoadROM(argv[1])) return 0;

	while (state == MainStates::Continue)
	{
		preciseTimer += (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f;
		lastTick = SDL_GetTicksNS();

		if (preciseTimer > LoopRate)
		{
			preciseTimer = 0.0f;
			switch (chip8.Update())
			{
			case (Globals::UpdateStatus::Exit):
				state = MainStates::Exit;
				break;

			}
		}
	}

	return 1;
}