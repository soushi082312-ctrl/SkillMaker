#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../TestMap/MapManager.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"

#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	InitPlayer();

	InitMap();

	InitCamera();
}

void LoadPlayScene()
{
    LoadPlayer();

	LoadMap();
}

void StartPlayScene()
{
	StartPlayer();

	StartMap();
}

void StepPlayScene()
{
	StepPlayer();

	StepCamera();
}

void UpdatePlayScene()
{
	UpdatePlayer();

	CheckCollision();
}

void DrawPlayScene()
{
	DrawPlayer();

	DrawMap();

	DrawCamera();
}

void FinPlayScene()
{
	FinMap();

	FinPlayer();
}