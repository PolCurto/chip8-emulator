#pragma once

#include <stdint.h>
#include <array>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

constexpr int Width = 64;
constexpr int Height = 32;

constexpr int Scale = 30;
constexpr int Pitch = sizeof(uint32_t) * Width;

class Window
{
public:
	Window() = default;
	~Window() = default;

	bool Init();
	bool Clear();

	void Render(const void* pixels);
	
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
};