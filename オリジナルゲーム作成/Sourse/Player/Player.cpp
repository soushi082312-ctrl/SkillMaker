#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"

#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULY_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (4.0f)

#define PLAYER_JUMP_POWER (10.0f)
#define PLAYER_GRAVITY (0.4f)

#define PLAYER_MAP_COLLISION_OFFSET (0.05f)
#define PLAYER_BOX_COLLISION_OFFSET_X (24)
#define PLAYER_BOX_COLLISION_OFFSET_Y (20)
#define PLAYER_BOX_COLLISION_WIDTH (20)
#define PLAYER_BOX_COLLISION_HEIGHT (44)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULY_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.active = false;
	
}

void LoadPlayer()
{

}

void StartPlayer()
{
	g_PlayerData.active = true;

	
}

void StepPlayer()
{
	if (!g_PlayerData.active)
	{
		return;
	}

	g_PrevPlayerData = g_PlayerData;

	g_PlayerData.moveX = 0.0f;

	g_PlayerData.moveY += PLAYER_GRAVITY;

	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}

	if (IsTriggerKey(KEY_SPACE))
	{
		g_PlayerData.moveY = -PLAYER_JUMP_POWER;
	}

	if (IsTriggerKey(KEY_F))
	{

	}
}

void UpdatePlayer()
{
	if (!g_PlayerData.active) return;

	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}

	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;
}

void DrawPlayer()
{
	if (!g_PlayerData.active) return;
}

void FinPlayer()
{

}

PlayerData GetPlayer()
{
	return g_PlayerData;
}

void PlayerHitNormalBlockX(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	player.isTurn = g_PrevPlayerData.isTurn;

	player.posX = g_PlayerData.posX;
	player.posY = g_PrevPlayerData.posY;

	float x, y, w, h;
	

	
}

void PlayerHitNormalBlockY(MapChipData mapChipData)
{

}