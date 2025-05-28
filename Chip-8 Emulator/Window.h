#pragma once

#include <stdint.h>
#include <array>

struct SDL_Window;

constexpr int Width = 64;
constexpr int Height = 32;

constexpr int Scale = 30;

class Window
{
public:
	Window() = default;
	~Window() = default;

	bool Init();
	bool Clear();
	
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

private:
	SDL_Window* window = nullptr;
};