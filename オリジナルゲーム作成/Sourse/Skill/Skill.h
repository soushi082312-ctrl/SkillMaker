#pragma once
#include "../Animation/Animation.h"
#include "DxLib.h"

enum SkillAnimationType
{
	SKILL_ANIM_POSE,
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

enum SkillType
{
	SKILL_FIRE,
	SKILL_WATER,
	SKILL_THUNDER,
	SKILL_METEOR,
	SKILL_PLATFORM,
	SKILL_TERRAIN,
	SKILL_BREAK_WALL,
	SKILL_TIME_STOP,
	SKILL_MAX,
};

struct SkillData
{
	bool active;
	bool isTurn;
	VECTOR pos;
	VECTOR move;
	int handle;
	int life;
	int Fire;
	int Water;
	int Thunder;
	int Platform;
	int Terrain;
	int Wall;
	int TimeStop;
	AnimationData animation[SKILL_ANIM_MAX];
	SkillAnimationType skillAnim;
};

void InitSkill();
void LoadSkill();
void StepSkill();
void UpdateSkill();
void DrawSkill();
void FinSkill();

void FireSkill(int life, VECTOR pos, VECTOR move, int Fire, int Water, int Thunder);

SkillData GetSkill();