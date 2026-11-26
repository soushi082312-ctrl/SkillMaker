#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../TestMap/MapManager.h"
#include "../../Player/Player.h"
#include "../../Enemy/EnemyManager.h"
#include "../../BackGround/BackGround.h"
#include "../../Skill/Skill.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"

void InitPlayScene()
{
	InitPlayer();

	InitEnemy();

	InitSkill();

	InitMap();

	InitCamera();
}

void LoadPlayScene()
{
    LoadPlayer();

	LoadEnemy();

	LoadSkill();

	LoadMap();
}

void StartPlayScene()
{
	StartPlayer();

	StartEnemy();

	StartMap();
}

void StepPlayScene()
{
	StepPlayer();

	StepEnemy();

	StepSkill();

	StepCamera();
}

void UpdatePlayScene()
{
	UpdatePlayer();

	UpdateEnemy();

	UpdateSkill();

	CheckCollision();
}

void DrawPlayScene()
{
	DrawPlayer();

	DrawEnemy();

	DrawSkill();

	DrawMap();

	DrawCamera();
}

void FinPlayScene()
{
	FinMap();

	FinPlayer();

	FinEnemy();

	FinSkill();
}