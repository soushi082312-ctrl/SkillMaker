#include "DxLib.h"
#include "Skill.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include <math.h>

struct SkillAnimationParm
{
	int interval;
	int frameNum;
	int width;
	int height;
};

const SkillAnimationParm SKILL_ANIM_PARAM[SKILL_ANIM_MAX] =
{
	5, 8, 108, 90,
	6, 8, 123, 90,
	6, 11, 109, 90,
	8, 10, 50, 90,
	10, 1, 100, 90,
};

#define SKILL_DEFAULT_POS_X (290.0f)
#define SKILL_DEFAULT_POS_Y (770.0f)

#define SKILL_ACTIVE_AREA_LEFT (60)
#define SKILL_ACTIVE_AREA_RIGHT (1240)
#define SKILL_ACTIVE_AREA_TOP (60)
#define SKILL_ACTIVE_AREA_BOTTOM (720)

SkillData g_SkillData = { 0 };

static int g_TimeStopTimer = 0;

void StartSkillAnimation(SkillAnimationType anim);

void InitSkill()
{
	g_SkillData.active = false;
	g_SkillData.pos.x = 0.0f;
	g_SkillData.pos.y = 0.0f;
	g_SkillData.move.x = 0.0f;
	g_SkillData.move.y = 0.0f;
	g_SkillData.handle = 0;
	g_SkillData.skillIntervalTimer = 0;
	g_SkillData.skillAnim = SKILL_ANIM_NONE;

	for (int i = 0; i < SKILL_ANIM_MAX; i++)
	{
		InitAnimation(&g_SkillData.animation[i]);
	}
}

void LoadSkill()
{
	g_SkillData.animation[SKILL_ANIM_FIRE].handle = LoadGraph("Data/Skill/火（範囲攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_WATER].handle = LoadGraph("Data/Skill/水（遠距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_THUNDER].handle = LoadGraph("Data/Skill/雷（近距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_METEO].handle = LoadGraph("Data/Skill/隕石（必殺技）.png");
	g_SkillData.animation[SKILL_ANIM_SCAFFOLD].handle = LoadGraph("Data/Skill/足場生成2.png");
	g_SkillData.animation[SKILL_ANIM_TIMESTOP].handle = LoadGraph("Data/Skill/時間停止.png");
}

void StartSkill(int selectedSkill, VECTOR pos, bool isTurn)
{
	
	switch (selectedSkill)
	{
	case 0:
		StartSkillAnimation(SKILL_ANIM_FIRE);
		break;

	case 1:
		StartSkillAnimation(SKILL_ANIM_WATER);
		break;

	case 2:
		StartSkillAnimation(SKILL_ANIM_THUNDER);
		break;

	case 3:
		StartSkillAnimation(SKILL_ANIM_METEO);
		break;

	case 4:
		StartSkillAnimation(SKILL_ANIM_SCAFFOLD);
		break;

	case 5:
		StartSkillAnimation(SKILL_ANIM_TIMESTOP);
		g_TimeStopTimer = 180;
		break;

	default:
		return;
	}

	g_SkillData.active = true;
	g_SkillData.pos.x = SKILL_DEFAULT_POS_X;
	g_SkillData.pos.y = SKILL_DEFAULT_POS_Y;

	g_SkillData.isTurn = isTurn;

	g_SkillData.skillIntervalTimer = 0;
}

void StepSkill()
{
	if (g_TimeStopTimer > 0)
	{
		g_TimeStopTimer--;
	}

	if (!g_SkillData.active)
	{
		return;
	}
}

void UpdateSkill()
{
	if (!g_SkillData.active)
	{
		return;
	}

	if (g_SkillData.skillAnim != SKILL_ANIM_NONE)
	{
		AnimationData* animData =
			&g_SkillData.animation[g_SkillData.skillAnim];

		UpdateAnimation(animData);

		g_SkillData.skillIntervalTimer++;

		if (g_SkillData.skillIntervalTimer > 60)
		{
			g_SkillData.active = false;
			g_SkillData.skillAnim = SKILL_ANIM_NONE;
			return;
		}
	}

	g_SkillData.pos.x += g_SkillData.move.x;
	g_SkillData.pos.y += g_SkillData.move.y;
}

void DrawSkill()
{
	if (!g_SkillData.active)
	{
		return;
	}

	if (g_SkillData.skillAnim == SKILL_ANIM_NONE)
	{
		return;
	}

	AnimationData* animData =
		&g_SkillData.animation[g_SkillData.skillAnim];

	DrawAnimation(
		animData,
		g_SkillData.pos.x,
		g_SkillData.pos.y,
		g_SkillData.isTurn
	);
}

void FinSkill()
{
	for (int i = 0; i < SKILL_ANIM_MAX; i++)
	{
		DeleteGraph(g_SkillData.animation[i].handle);
	}
}

void StartSkillAnimation(SkillAnimationType anim)
{
	if (anim == g_SkillData.skillAnim) return;

	g_SkillData.skillAnim = anim;

	AnimationData* animData = &g_SkillData.animation[anim];
	SkillAnimationParm animParam = SKILL_ANIM_PARAM[anim];

	StartAnimation(animData, g_SkillData.pos.x, g_SkillData.pos.y, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}


SkillData GetSkill()
{
	return g_SkillData;
}

bool IsTimeStopActive()
{
	return g_TimeStopTimer > 0;
}