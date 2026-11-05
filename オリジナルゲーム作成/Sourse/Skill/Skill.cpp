#include "DxLib.h"
#include "Skill.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"

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
	8, 8, 90, 90,
	5, 8, 90, 90,
};

#define SKILL_DEFAULT_POS_X (0.0f)
#define SKILL_DEFAULT_POS_Y (0.0f)
#define SKILL_MOVE_SPEED (4.0f)

SkillData g_SkillData = { 0 };

void StartSkillAnimation(SkillAnimationType anim);
void UpdateSkillAnimation();

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

	if (IsTriggerKey(KEY_D))
	{
		ChangeScene(SCENE_RESULT);
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
	for (int i = 0; i < SKILL_ANIM_MAX; i++)
	{
		DeleteGraph(g_SkillData.animation[i].handle);
	}
}

SkillData GetSkill()
{
	return g_SkillData;
}

void StartSkillAnimation(SkillAnimationType anim)
{
	if (anim == g_SkillData.skillAnim) return;
	g_SkillData.skillAnim = anim;
	AnimationData* animData = &g_SkillData.animation[anim];
	SkillAnimationParam animParam = SKILL_ANIM_PARAM[anim];
	StartAnimation(animData, g_SkillData.pos.x, g_SkillData.pos.y, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdateSkillAnimation()
{
	if (g_SkillData.active)
	{
		AnimationData* animData = &g_SkillData.animation[g_SkillData.skillAnim];
		UpdateAnimation(animData);
	}
}