#pragma once

enum InputKey
{
	KEY_UP		= (1 << 0),
	KEY_DOWN	= (1 << 1),
	KEY_LEFT	= (1 << 2),
	KEY_RIGHT	= (1 << 3),
	KEY_SPACE	= (1 << 4),
	KEY_F		= (1 << 5),
	KEY_S		= (1 << 6),
	KEY_D		= (1 << 7),
};

void InitInput();
void UpdateInput();
void DrawInput();
void FinInput();

bool IsInputKey(InputKey key);
bool IsTriggerKey(InputKey key);
