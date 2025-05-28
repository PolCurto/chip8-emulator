#include "Chip8_Core.h"

Chip8_Core::Chip8_Core()
{
	window.Init();
	input.Init();
}

Chip8_Core::~Chip8_Core()
{
	input.Clear();
	window.Clear();
}

Globals::UpdateStatus Chip8_Core::Update()
{
	Globals::UpdateStatus status = Globals::UpdateStatus::Continue;

	UpdateTimers();
	status = input.Update();

	return status;
}

void Chip8_Core::UpdateTimers()
{
	if (delayTimer > 0) --delayTimer;
	if (audioTimer > 0) --audioTimer;
}