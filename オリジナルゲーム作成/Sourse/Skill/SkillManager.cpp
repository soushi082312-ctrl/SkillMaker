#include "SkillManager.h"
#include "Skill.h"

void InitAllSkill()
{
	InitSkill();
}

void LoadAllSkill()
{
	LoadSkill();
}

void StepAllSkill()
{
	StepSkill();
}

void UpdateAllSkill()
{
	UpdateSkill();
}

void DrawAllSkill()
{
	DrawSkill();
}

void FinAllSkill()
{
	FinSkill();
}

void RequestFireBullet(int life, VECTOR pos, VECTOR move, int Fire, int Water, int Thunder)
{
	FireSkill(life, pos, move, Fire, Water, Thunder);
}