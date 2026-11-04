#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Collision/Collision.h"

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

void MoveWithMapCollision(Body* body)
{
	body->pos.x += body->move.x;

	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			MapChipData mapChipData = GetMapChipData(x, y);
			if (mapChipData.mapChip == 0) continue;

			BlockData* block = mapChipData.data;
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height,
				                  block->pos.x, block->pos.y, block->width, block->height));

			if (body->move.x > 0.0f)
			{
				body->pos.x -= (body->pos.x + body->width) - block->pos.x;
			}
			else if (body->move.x < 0.0f)
			{
				body->pos.x += (block->pos.x + block->width) - body->pos.x;
			}

			body->move.x = 0.0f;
		}
	}

	body->pos.y += body->move.y;

	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			MapChipData mapChipData = GetMapChipData(x, y);
			if (mapChipData.mapChip == 0) continue;
			BlockData* block = mapChipData.data;
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height,
								  block->pos.x, block->pos.y, block->width, block->height));
			if (body->move.y > 0.0f)
			{
				body->pos.y -= (body->pos.y + body->height) - block->pos.y;
				body->isAir = false;
			}
			else if (body->move.y < 0.0f)
			{
				body->pos.y += (block->pos.y + block->height) - body->pos.y;
			}
			
			body->move.y = 0.0f;
		}
	}
}
