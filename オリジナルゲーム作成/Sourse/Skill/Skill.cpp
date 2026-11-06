#include "DxLib.h"
#include "Skill.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"


SkillData g_SkillData = { 0 };


void InitSkill()
{
	g_SkillData.active = false;
	g_SkillData.pos.x = 0.0f;
	g_SkillData.pos.y = 0.0f;
}

void LoadSkill()
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

SkillData GetSkill()
{
	return g_SkillData;
}