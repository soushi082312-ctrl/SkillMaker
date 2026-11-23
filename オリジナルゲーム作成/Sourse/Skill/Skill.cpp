#include "DxLib.h"
#include "Skill.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Camera/Camera.h"
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
	8, 11, 500, 90,
	10, 8, 65, 90,
	8, 11, 107, 90,
	8, 10, 50, 90,
	5, 1, 150, 90,
	8, 3, 300, 170,
};

#define SKILL_DEFAULT_POS_X (290.0f)
#define SKILL_DEFAULT_POS_Y (770.0f)

#define SKILL_ACTIVE_AREA_LEFT (60)
#define SKILL_ACTIVE_AREA_RIGHT (1240)
#define SKILL_ACTIVE_AREA_TOP (60)
#define SKILL_ACTIVE_AREA_BOTTOM (720)

SkillData g_SkillData = { 0 };

void UpdateSkillAnimation();

static int g_TimeStopTimer = 0;

static VECTOR g_PlatformPos = VGet(0.0f, 0.0f, 0.0f);
static bool g_PlatformActive = false;
static bool g_PlatformTurn = false;
static int g_PlatformLife = 0;

void InitSkill()
{
	g_SkillData.active = false;
	g_SkillData.pos.x = 0.0f;
	g_SkillData.pos.y = 0.0f;
	g_SkillData.move.x = 0.0f;
	g_SkillData.move.y = 0.0f;
	g_SkillData.handle = 0;
	g_SkillData.life = 0;
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

void StepSkill()
{
	if (g_TimeStopTimer > 0)
	{
		g_TimeStopTimer--;
	}

	if (g_PlatformActive)
	{
		g_PlatformLife--;

		if (g_PlatformLife <= 0)
		{
			g_PlatformActive = false;
		}
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
	}
}

void DrawSkill()
{
	CameraData camera = GetCamera();

	if (g_PlatformActive)
	{
		AnimationData* platformAnim =
			&g_SkillData.animation[SKILL_ANIM_SCAFFOLD];

		DrawAnimation(
			platformAnim,
			g_PlatformPos.x - camera.pos.x,
			g_PlatformPos.y - camera.pos.y,
			g_PlatformTurn
		);
	}

	if (!g_SkillData.active)
	{
		return;
	}

	if (g_SkillData.skillAnim == SKILL_ANIM_NONE ||
		g_SkillData.skillAnim == SKILL_ANIM_SCAFFOLD)
	{
		return;
	}

	AnimationData* animData =
		&g_SkillData.animation[g_SkillData.skillAnim];

	DrawAnimation(
		animData,
		g_SkillData.pos.x - camera.pos.x,
		g_SkillData.pos.y - camera.pos.y,
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

	StartAnimation(
		animData,
		g_SkillData.pos.x,
		g_SkillData.pos.y,
		animParam.interval,
		animParam.frameNum,
		animParam.width,
		animParam.height,
		true
	);
}

void FireSkill(int life, VECTOR pos, VECTOR move, int Fire, int Water, int Thunder)
{
	SkillData* skill = &g_SkillData;
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (!skill->active)
		{
			skill->active = true;

			

			skill->life = life;

			skill->pos.x = pos.x;
			skill->pos.y = pos.y;

			skill->move.x = move.x;
			skill->move.y = move.y;

			skill->Fire = Fire;
			skill->Water = Water;
			skill->Thunder = Thunder;

			break;
		}
	}
}

SkillData GetSkill()
{
	return g_SkillData;
}

void StartSkill(int selectedSkill, VECTOR pos, bool isTurn)
{
	SkillAnimationType anim = SKILL_ANIM_NONE;

	switch (selectedSkill)
	{
	case 0:
		anim = SKILL_ANIM_FIRE;
		break;

	case 1:
		anim = SKILL_ANIM_WATER;
		break;

	case 2:
		anim = SKILL_ANIM_THUNDER;
		break;

	case 3:
		anim = SKILL_ANIM_METEO;
		break;

	case 4:
		g_PlatformPos = pos;

		if (isTurn)
			g_PlatformPos.x -= 150.0f;
		else
			g_PlatformPos.x += 50.0f;

		g_PlatformPos.y += 64.0f;

		g_PlatformTurn = isTurn;
		g_PlatformActive = true;
		g_PlatformLife = 600;

		StartAnimation(
			&g_SkillData.animation[SKILL_ANIM_SCAFFOLD],
			g_PlatformPos.x,
			g_PlatformPos.y,
			5, 1, 150, 90, true
		);

		return;

	case 5:
		anim = SKILL_ANIM_TIMESTOP;
		g_TimeStopTimer = 180;
		break;

	default:
		return;
	}

	g_SkillData.pos.x = SKILL_DEFAULT_POS_X;
	g_SkillData.pos.y = SKILL_DEFAULT_POS_Y;
	g_SkillData.isTurn = isTurn;
	g_SkillData.active = true;
	
	StartSkillAnimation(anim);
}

void UpdateSkillAnimation()
{
	SkillAnimationType animType = g_SkillData.skillAnim;
	AnimationData* animData = &g_SkillData.animation[animType];
	UpdateAnimation(animData);
}

bool IsTimeStopActive()
{
	return g_TimeStopTimer > 0;
}

bool GetSkillPlatform(float& left, float& top, float& right)
{
	if (!g_PlatformActive)
	{
		return false;
	}

	left = g_PlatformPos.x;
	top = g_PlatformPos.y;
	right = left + 150.0f;

	return true;
}