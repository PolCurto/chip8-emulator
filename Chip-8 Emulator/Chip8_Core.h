#pragma once

#include "Window.h"
#include "Input.h"
#include "Globals.h"

#include <stack>
#include <stdint.h>


constexpr int RAMSize = 4096;

class Chip8_Core
{
public:
	Chip8_Core();
	~Chip8_Core();

	Globals::UpdateStatus Update();

private:
	void UpdateTimers();

private:
	Window window;
	Input input;

	uint8_t memory[RAMSize];
	uint16_t programCounter = 0;
	uint16_t indexRegister = 0;
	std::stack<uint16_t> stack; // TODO: Maybe limit the stack

	uint8_t delayTimer = 0;
	uint8_t audioTimer = 0;

	uint8_t variableRegisters[16];

	//TODO: ROMS adress from 000 to 1FF is empty (The font go there)
};