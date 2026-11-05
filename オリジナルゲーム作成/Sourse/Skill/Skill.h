#pragma once
#include "../Animation/Animation.h"

enum SkillAnimationType
{
	SKILL_ANIM_FIRE,
	SKILL_ANIM_WATER,
	SKILL_ANIM_THUNDER,
	SKILL_ANIM_METEO,
	SKILL_ANIM_SCAFFOLD,
	SKILL_ANIM_CHANGE,
	SKILL_ANIM_WALL,
	SKILL_ANIM_TIMESTOP,
	SKILL_ANIM_MAX,
	SKILL_ANIM_NONE = -1
};

struct SkillData
{
	bool active;
	VECTOR pos;
	VECTOR move;
	int handle;
	int Fire;
	int Water;
	int Thunder;
	AnimationData animation[SKILL_ANIM_MAX];
	SkillAnimationType skillAnim;
};

void InitSkill();
void LoadSkill();
void StartSkill();
void StepSkill();
void UpdateSkill();
void DrawSkill();
void FinSkill();

SkillData GetSkill();