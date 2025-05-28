#pragma once

struct SDL_Window;


constexpr int Width = 100;
constexpr int Height = 100;

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