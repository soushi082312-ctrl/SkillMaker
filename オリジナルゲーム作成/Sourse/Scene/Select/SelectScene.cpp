#include "DxLib.h"
#include "SelectScene.h"
#include "../../Input/Input.h"
#include "../SceneManager.h"

static int g_SelectedSkill = 0;

static int g_SkillHandle[7];

void InitSelectScene() 
{
	g_SelectedSkill = 0;
}

void LoadSelectScene() 
{
	g_SkillHandle[0] = LoadGraph("Data/Skill/");
}

void StartSelectScene() 
{
}

void StepSelectScene() 
{
	if (IsTriggerKey(KEY_LEFT))
	{
		g_SelectedSkill--;

		if (g_SelectedSkill < 0)
			g_SelectedSkill = 6;
	}

	if (IsTriggerKey(KEY_RIGHT))
	{
		g_SelectedSkill++;

		if (g_SelectedSkill < 6)
			g_SelectedSkill = 0;
	}

	if (IsTriggerKey(KEY_D))
	{
		ChangeScene(SCENE_PLAY);
	}
}

void UpdateSelectScene() 
{

}

void DrawSelectScene() 
{
	DrawString(700, 100, "スキル一覧", GetColor(255, 255, 255));
}

void FinSelectScene() 
{

}