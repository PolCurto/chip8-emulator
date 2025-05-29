#include "Input.h"

#include "Globals.h"

#include <SDL3/SDL.h>
#include <iostream>

bool Input::Init()
{
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		std::cerr << "SDL_EVENTS could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		ret = false;
	}


	return ret;
}

bool Input::Clear()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

Globals::UpdateStatus Input::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			return Globals::UpdateStatus::Exit;
		}
	}

	const bool* keyboard = SDL_GetKeyboardState(NULL);
	for (std::pair<SDL_Scancode, bool>& key : keys)
	{
		key.second = keyboard[key.first];
	}

	return Globals::UpdateStatus::Continue;
}

bool Input::IsKeyDown(const uint8_t key)
{
	return keys[key].second;
}

bool Input::IsAnyKeyDown()
{
	for (std::pair<SDL_Scancode, bool>& key : keys)
	{
		if (key.second) return true;
	}
	return false;
}

uint8_t Input::GetCurrentKeyDown()
{
	for (uint8_t i = 0; i < keys.size(); ++i)
	{
		if (keys[i].second) return i;
	}

	return 0;
}