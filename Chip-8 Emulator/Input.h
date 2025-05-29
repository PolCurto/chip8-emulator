#pragma once

#include "Globals.h"

#include <SDL3/SDL_scancode.h>
#include <array>

class Input
{
public:
	Input() = default;
	~Input() = default;

	bool Init();
	bool Clear();
	Globals::UpdateStatus Update();

	bool IsKeyDown(const uint8_t key);
	bool IsAnyKeyDown();

private:
	std::array<std::pair<SDL_Scancode, bool>, 16> keys = {
		std::make_pair(SDL_SCANCODE_1, false), std::make_pair(SDL_SCANCODE_2, false), std::make_pair(SDL_SCANCODE_1, false), std::make_pair(SDL_SCANCODE_4, false),
		std::make_pair(SDL_SCANCODE_Q, false), std::make_pair(SDL_SCANCODE_W, false), std::make_pair(SDL_SCANCODE_E, false), std::make_pair(SDL_SCANCODE_R, false),
		std::make_pair(SDL_SCANCODE_A, false), std::make_pair(SDL_SCANCODE_S, false), std::make_pair(SDL_SCANCODE_D, false), std::make_pair(SDL_SCANCODE_F, false),
		std::make_pair(SDL_SCANCODE_Z, false), std::make_pair(SDL_SCANCODE_X, false), std::make_pair(SDL_SCANCODE_C, false), std::make_pair(SDL_SCANCODE_V, false)
	};

};