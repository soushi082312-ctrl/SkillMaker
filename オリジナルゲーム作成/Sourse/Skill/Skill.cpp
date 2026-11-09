#include "DxLib.h"
#include "Skill.h"
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
	8, 10, 50, 90,
	8, 8, 50, 90,
	8, 11, 50, 90,

};

#define SKILL_DEFAULT_POS_X (100.0f)
#define SKILL_DEFAULT_POS_Y (786.0f)

#define SKILL_ACTIVE_AREA_LEFT (60)
#define SKILL_ACTIVE_AREA_RIGHT (1240)
#define SKILL_ACTIVE_AREA_TOP (60)
#define SKILL_ACTIVE_AREA_BOTTOM (720)

SkillData g_SkillData = { 0 };

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
}

void StepSkill()
{
	SkillData* skill = &g_SkillData;
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (!skill->active)continue;

		skill->life--;
	}
}

void UpdateSkill()
{
	SkillData* skill = &g_SkillData;
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (!skill->active)continue;

		if (skill->life <= 0)
		{
			skill->active = false;
		}

		if (skill->pos.x <= SKILL_ACTIVE_AREA_LEFT || skill->pos.x >= SKILL_ACTIVE_AREA_RIGHT)
		{
			skill->active = false;
		}
		else if (skill->pos.y <= SKILL_ACTIVE_AREA_TOP || skill->pos.y >= SKILL_ACTIVE_AREA_BOTTOM)
		{
			skill->active = false;
		}
		
	}
}

void DrawSkill()
{
	SkillData* skill = &g_SkillData;
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (!skill->active)continue;

		SkillAnimationType animType = g_SkillData.skillAnim;
		AnimationData* animData = &g_SkillData.animation[animType];
		DrawAnimation(animData, g_SkillData.pos.x, g_SkillData.pos.y, g_SkillData.isTurn);

	}
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

void FireSkill(int life, VECTOR pos, VECTOR move, int Fire, int Water, int Thunder)
{
	SkillData* skill = &g_SkillData;
	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		if (!skill->active)
		{
			skill->active = true;

			if (Thunder)
			{
				skill->Thunder = g_SkillData.animation[SKILL_ANIM_THUNDER].handle;
			}
			else if (Water)
			{
				skill->Water = g_SkillData.animation[SKILL_ANIM_WATER].handle;
			}
			else if (Fire)
			{
				skill->Fire = g_SkillData.animation[SKILL_ANIM_FIRE].handle;
			}

			skill->life = life;


		}
	}
}

SkillData GetSkill()
{
	return g_SkillData;
}