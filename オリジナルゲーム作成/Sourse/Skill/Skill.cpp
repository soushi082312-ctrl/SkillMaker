#include "DxLib.h"
#include "Skill.h"
#include "../Input/Input.h"

struct SkillAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};

const SkillAnimationParam SKILL_ANIM_PARAM[SKILL_ANIM_MAX] =
{
	8, 8, 73, 90,
};

#define SKILL_DEFAULT_POS_X (0.0f)
#define SKILL_DEFAULT_POS_Y (0.0f)
#define SKILL_MOVE_SPEED (4.0f)

SkillData g_SkillData = { 0 };

void InitSkill()
{
	
}

void LoadSkill()
{
	g_SkillData.animation[SKILL_ANIM_FIRE].handle = LoadGraph("Data/Skill/火（範囲攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_WATER].handle = LoadGraph("Data/Skill/水（遠距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_THUNDER].handle = LoadGraph("Data/Skill/雷（近距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_METEO].handle = LoadGraph("Data/Skill/隕石（必殺技）.png");
	g_SkillData.animation[SKILL_ANIM_SCAFFOLD].handle = LoadGraph("Data/Skill/足場生成.png");
}

void StartSkill()
{
	g_SkillData.active = true;
}

void StepSkill()
{
	if (!g_SkillData.active)
	{
		return;
	}

	if (IsInputKey(KEY_D))
	{

	}

	if (IsTriggerKey(KEY_S))
	{
		g_SkillData.move.x = SKILL_MOVE_SPEED;
	}
}

void UpdateSkill()
{
	
}

void DrawSkill()
{
	
}

void FinSkill()
{
	
}

