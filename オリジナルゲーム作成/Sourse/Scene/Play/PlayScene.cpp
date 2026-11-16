#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../TestMap/MapManager.h"
#include "../../Player/Player.h"
#include "../../BackGround/BackGround.h"
#include "../../Skill/Skill.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"

void InitPlayScene()
{
	InitPlayer();

	InitSkill();

	InitMap();

	InitCamera();
}

void LoadPlayScene()
{
    LoadPlayer();

	LoadSkill();

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

	StepSkill();

	StepCamera();
}

void UpdatePlayScene()
{
	UpdatePlayer();

	UpdateSkill();

	CheckCollision();
}

void DrawPlayScene()
{
	DrawPlayer();

	DrawSkill();

	DrawMap();

	DrawCamera();
}

void FinPlayScene()
{
	FinMap();

	FinPlayer();

	FinSkill();
}