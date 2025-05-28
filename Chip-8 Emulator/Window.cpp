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

		renderer = SDL_CreateRenderer(window, nullptr);
		if (renderer == nullptr)
		{
			std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			status = false;
		}


		texture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Width, Height);
		if (texture == nullptr)
		{
			std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
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

void Window::Render(const void* pixels)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_UpdateTexture(texture, nullptr, pixels, Pitch);
	SDL_RenderTexture(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}