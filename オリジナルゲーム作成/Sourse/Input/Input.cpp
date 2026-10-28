#include "DxLib.h"
#include "Input.h"

int g_InputState = 0;
int g_PervInputState = 0;

void InitInput()
{
	g_InputState = 0;
	g_PervInputState = 0;
}

void UpdateInput()
{
	g_PervInputState = g_InputState;

	g_InputState = 0;

	if (CheckHitKey(KEY_INPUT_UP))
	{
		g_InputState |= KEY_UP;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		g_InputState |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		g_InputState |= KEY_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		g_InputState |= KEY_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		g_InputState |= KEY_SPACE;
	}
	if (CheckHitKey(KEY_INPUT_F))
	{
		g_InputState |= KEY_F;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		g_InputState |= KEY_S;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		g_InputState |= KEY_D;
	}
}

void DrawInput()
{
}

void FinInput()
{
}

bool IsInputKey(InputKey key)
{
	return g_InputState & key;
}

bool IsTriggerKey(InputKey key)
{
	return (g_InputState & key) && !(g_PervInputState & key);
}