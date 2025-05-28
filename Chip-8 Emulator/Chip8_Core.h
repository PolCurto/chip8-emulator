#pragma once

#include "Window.h"

#include <stack>
#include <stdint.h>


constexpr int RAMSize = 4096;

class Chip8_Core
{
public:
	Chip8_Core();
	~Chip8_Core();

private:
	Window window;

	uint8_t memory[RAMSize];
	uint16_t programCounter;
	uint16_t indexRegister;
	std::stack<uint16_t> stack;

	uint8_t delayTimer;
	uint8_t audioTimer;

	uint8_t variableRegisters[16];

	//TODO: ROMS adress from 000 to 1FF is empty (The font go there)
};