#include "Chip8.h"
#include "Font.h"

#include <fstream>
#include <cassert>

Chip8::Chip8()
{
	window.Init();
	input.Init();

	for (int i = 0; i < Font::DataSize; ++i)
	{
		memory[Font::Adress + i] = Font::Data[i];
	}
}

Chip8::~Chip8()
{
	input.Clear();
	window.Clear();
}

Globals::UpdateStatus Chip8::Update()
{
	Globals::UpdateStatus status = Globals::UpdateStatus::Continue;

	UpdateTimers();
	status = input.Update();

	uint16_t opcode = Fetch();
	Decode(opcode);

	window.Render(pixels);

	return status;
}

uint16_t Chip8::Fetch()
{
	uint16_t opcode = (memory[programCounter] << 8) | memory[programCounter + 1];

	programCounter += 2;
	return opcode;
}

void Chip8::Decode(uint16_t opcode)
{
	uint8_t firstNibble = (opcode & 0xF000) >> 12;

	uint8_t x = (opcode & 0x0F00) >> 8;
	uint8_t y = (opcode & 0x00F0) >> 4;
	uint8_t n = opcode & 0x000F;

	uint8_t nn = opcode & 0x00FF;
	uint16_t nnn = opcode & 0x0FFF;

	// THE switch
	switch (firstNibble)
	{
	case (0x0):
		switch (nnn)
		{
		case (0x0E0):
			memset(pixels, 0, sizeof(pixels));
			break;

		case (0x0EE):
			programCounter = stack.top();
			stack.pop();
			break;
		}
		break;

	case (0x1):
		programCounter = nnn;
		break;

	case (0x2):
		stack.push(programCounter);
		programCounter = nnn;
		break;

	case (0x3):
		break;
	case (0x4):
		break;
	case (0x5):
		break;

	case (0x6):
		variableRegisters[x] = nn;
		break;

	case (0x7):
		variableRegisters[x] += nn;
		break;

	case (0x8):
		break;

	case (0x9):
		break;

	case (0xA):
		indexRegister = nnn;
		break;

	case (0xB):
		break;

	case (0xC):
		break;

	case (0xD):
	{
		const uint8_t vx = variableRegisters[x] & 63;
		uint8_t vy = variableRegisters[y] & 31;
		variableRegisters[0XF] = 0;

		for (uint8_t i = 0; i < n; ++i)
		{
			const uint8_t spriteData = memory[indexRegister + i];
			uint8_t px = vx;
			for (int j = 0; j < 8; ++j)
			{
				bool bit = (spriteData >> (7 - j)) & 0x0F;
				if (bit)
				{
					int index = vy * window.GetWidth() + px;
					if (pixels[index] == 0xFFFFFFFF)
					{
						variableRegisters[0xF] = 1;
						pixels[index] = 0x000000FF;
					}
					else
					{
						pixels[index] = 0xFFFFFFFF;
					}
				}
				++px;
				if (px == window.GetWidth()) break;
			}
			++vy;
			if (vy == window.GetHeight()) break;
		}
		break;
	}

	case (0xE):
		break;

	case (0xF):
		break;
	}
}

void Chip8::LoadROM(const char* filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i)
		{
			memory[StartAdress + i] = buffer[i];
		}

		delete[] buffer;
	}
}

void Chip8::UpdateTimers()
{
	if (delayTimer > 0) --delayTimer;
	if (audioTimer > 0) --audioTimer;
}