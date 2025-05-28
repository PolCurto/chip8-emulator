#pragma once

struct SDL_Window;

constexpr int Width = 64;
constexpr int Height = 32;

constexpr int Scale = 10;

class Window
{
public:
	Window() = default;
	~Window() = default;

	bool Init();
	bool Clear();

private:
	SDL_Window* window = nullptr;
};