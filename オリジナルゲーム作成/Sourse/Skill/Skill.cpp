#include "DxLib.h"
#include "Skill.h"

struct SkillAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
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
	g_SkillData.animation[SKILL_ANIM_SCAFFOLD].handle = LoadGraph("Data/Skill/足場生成.png");
}

void StartSkill()
{
	
}

void StepSkill()
{
	
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

