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

	randByte = std::uniform_int_distribution<unsigned int>(0, 255U);
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
		if (registers[x] == nn) programCounter += 2;
		break;

	case (0x4):
		if (registers[x] != nn) programCounter += 2;
		break;

	case (0x5):
		if (registers[x] == registers[y]) programCounter += 2;
		break;

	case (0x6):
		registers[x] = nn;
		break;

	case (0x7):
		registers[x] += nn;
		break;

	case (0x8):
		switch (n)
		{
		case (0):
			registers[x] = registers[y];
			break;

		case (1):
			registers[x] = registers[x] | registers[y];
			break;

		case (2):
			registers[x] = registers[x] & registers[y];
			break;

		case (3):
			registers[x] = registers[x] ^ registers[y];
			break;

		case (4):
			if (static_cast<int>(registers[x] + registers[y]) > UINT8_MAX) registers[0xF] = 1;
			else registers[0xF] = 1;
			registers[x] += registers[y];
			break;

		case (5):
			if (registers[x] > registers[y]) registers[0xF] = 1;
			else registers[0xF] = 0;
			registers[x] = registers[x] - registers[y];
			break;

		case (6):
		{
			// Old version: registers[x] = registers[y];
			bool bit = registers[x] & 0x01;
			if (bit) registers[0xF] = 1;
			else registers[0xF] = 0;
			registers[x] = registers[x] >> 1;
			break;
		}
			

		case (7):
			if (registers[y] > registers[x]) registers[0xF] = 1;
			else registers[0xF] = 0;
			registers[x] = registers[y] - registers[x];
			break;

		case (0xE):
		{
			// Old version: registers[x] = registers[y];
			bool bit = (registers[x] >> 7) & 0x01;
			if (bit) registers[0xF] = 1;
			else registers[0xF] = 0;
			registers[x] = registers[x] << 1;
			break;
		}
			
		}
		break;

	case (0x9):
		if (registers[x] != registers[y]) programCounter += 2;
		break;

	case (0xA):
		indexRegister = nnn;
		break;

	case (0xB):
		//programCounter = nnn + registers[0]; // Old
		programCounter = nnn + registers[x]; // New
		break;

	case (0xC):
		registers[x] = static_cast<uint8_t>(randByte(randGen)) & nn;
		break;

	case (0xD):
	{
		const uint8_t vx = registers[x] & 63;
		uint8_t vy = registers[y] & 31;
		registers[0XF] = 0;

		for (uint8_t i = 0; i < n; ++i)
		{
			const uint8_t spriteData = memory[indexRegister + i];
			uint8_t px = vx;
			for (int j = 0; j < 8; ++j)
			{
				bool bit = (spriteData >> (7 - j)) & 0x01;
				if (bit)
				{
					int index = vy * window.GetWidth() + px;
					if (pixels[index] == 0xFFFFFFFF)
					{
						registers[0xF] = 1;
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
		switch (nn)
		{
		case (0x9E):
			if (input.IsKeyDown(registers[x])) programCounter += 2;
			break;

		case (0xA1):
			if (!input.IsKeyDown(registers[x])) programCounter += 2;
			break;
		}
		break;

	case (0xF):
		switch (nn)
		{
		case (0x07):
			registers[x] = delayTimer;
			break;

		case (0x15):
			delayTimer = registers[x];
			break;

		case (0x18):
			audioTimer = registers[x];
			break;

		case (0x1E):
			indexRegister += registers[x];
			// TODO: Some games need the VF flagged as 1 if this overflows
			break;

		case (0x0A):
			if (input.IsAnyKeyDown()) registers[x] = 0x01; // TODO: Get the hex value of the inputted key
			else programCounter -= 2;
			break;

		case (0x29):
			indexRegister = Font::Adress;
			break;

		case (0x33):
		{
			// Split the hex value in three decimal values
			const uint8_t hex = registers[x];
			const uint8_t firstDigit = hex / 100;
			const uint8_t secondDigit = (hex / 10) % 10;
			const uint8_t thirdDigit = hex % 10;

			memory[indexRegister] = firstDigit;
			memory[indexRegister + 1] = secondDigit;
			memory[indexRegister + 2] = thirdDigit;
			break;
		}
			
		case (0x55):
			for (uint8_t i = 0; i <= x; ++i)
			{
				memory[indexRegister + i] = registers[i];
			}
			break;

		case (0x65):
			for (uint8_t i = 0; i <= x; ++i)
			{
				 registers[i] = memory[indexRegister + i];
			}
			break;
		}

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