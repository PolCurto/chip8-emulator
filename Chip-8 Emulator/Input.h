#pragma once

#include "Globals.h"

#include <SDL3/SDL_scancode.h>

class Input
{
public:
	Input() = default;
	~Input() = default;

	bool Init();
	bool Clear();
	Globals::UpdateStatus Update();

private:
	SDL_Scancode keys[16] = {
		SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4,
		SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_R,
		SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F,
		SDL_SCANCODE_Z, SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_V
	};
};