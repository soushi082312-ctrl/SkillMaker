#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"

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

