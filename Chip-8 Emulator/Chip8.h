#pragma once

#include "Window.h"
#include "Input.h"
#include "Globals.h"

#include <stack>
#include <stdint.h>
#include <random>

constexpr int RAMSize = 4096;

constexpr int StartAdress = 0x200;

class Chip8
{
public:
	Chip8();
	~Chip8();

	Globals::UpdateStatus Update();

	void LoadROM(const char* filename);

private:
	void UpdateTimers();
	uint16_t Fetch();
	void Decode(uint16_t opcode);

private:
	Window window;
	Input input;

	uint8_t memory[RAMSize];
	uint16_t programCounter = StartAdress;
	uint16_t indexRegister = 0x000;
	std::stack<uint16_t> stack; // TODO: Maybe limit the stack

	uint8_t delayTimer = UINT8_MAX;
	uint8_t audioTimer = UINT8_MAX;

	std::array<uint8_t, 16> registers;
	uint32_t pixels[Width * Height];

	std::default_random_engine randGen;
	std::uniform_int_distribution<unsigned int> randByte;

	//TODO: ROMS adress from 000 to 1FF is empty (The font go there)
};