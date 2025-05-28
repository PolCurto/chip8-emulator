#include "Window.h"

#include <SDL3/SDL.h>
#include "SDL3/SDL_video.h"
#include <iostream>

bool Window::Init()
{
	bool status = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL_VIDEO could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		status = false;
	}
	else
	{
		//Create window
		int width = Width * Scale;
		int height = Height * Scale;

		window = SDL_CreateWindow("Chip-8", width, height, 0);

		if (window == nullptr)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			status = false;
		}
	}

	return status;

}

bool Window::Clear()
{
	//Destroy window
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}