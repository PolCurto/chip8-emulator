#include "Chip8.h"
#include "Globals.h"

#include <SDL3/SDL_timer.h>
#include <iostream>

constexpr float LoopRate = 0.8f;

enum class MainStates
{
	Continue,
	Exit
};

int main()
{
	//TODO: Initialize things
	Chip8 chip8;

	uint64_t timer = SDL_GetTicks();
	MainStates state = MainStates::Continue;

	uint64_t lastTick = 0;
	uint64_t freq = SDL_GetPerformanceFrequency();;
	float preciseTimer = 0;

	//chip8.LoadROM("IBM Logo.ch8");
	//chip8.LoadROM("BC_test.ch8");
	//chip8.LoadROM("test_opcode.ch8");
	//chip8.LoadROM("Tetris.ch8");
	//chip8.LoadROM("Pong.ch8");
	chip8.LoadROM("brix.ch8");
	//chip8.LoadROM("Most Dangerous Game.ch8");
	//chip8.LoadROM("Cave.ch8");

	while (state == MainStates::Continue)
	{
		//TODO: Main loop
		preciseTimer += (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f;
		lastTick = SDL_GetTicksNS();

		//std::cout << "precise timer: " << preciseTimer << std::endl;
		if (preciseTimer > LoopRate)
		{
			preciseTimer = 0.0f;
			// TODO Get this out of here, manage timer inside
			switch (chip8.Update())
			{
			case (Globals::UpdateStatus::Exit):
				state = MainStates::Exit;
				break;

			}
		}
	}

	return 0;
}