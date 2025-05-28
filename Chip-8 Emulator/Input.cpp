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

	return Globals::UpdateStatus::Continue;
}