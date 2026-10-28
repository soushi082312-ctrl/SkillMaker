#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Player/Player.h"

#define CHECK_ROUND_NUM (2)

void InitMap()
{
}

void LoadMap()
{
    LoadBlock();
    LoadMapChipData();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	DrawBlock();
}

void FinMap()
{
}

void ChceckMapPlayerCollision()
{
	PlayerData player = GetPlayer();
	
	int playerX = (int)(player.posX / MAP_CHIP_WIDTH);
	int playerY = (int)((player.posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	int left = playerX - CHECK_ROUND_NUM;
	int top = playerY - CHECK_ROUND_NUM;
	int right = playerX + CHECK_ROUND_NUM;
	int bottom = playerY + CHECK_ROUND_NUM;


	for (int y = top; y <= bottom; y++)
	{
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockX(mapChipData);
				break;
			}
		}
	}

	for (int y = top; y <= bottom; y++)
	{
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockY(mapChipData);
				break;
			}
		}
	}

}