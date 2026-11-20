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

void StartSkill(int skillType)
{
    switch (skillType)
    {
    case 0:
        // 火：範囲攻撃
        // 火の攻撃処理
        break;

    case 1:
        // 水：遠距離攻撃
        // 水の弾を発射
        break;

    case 2:
        // 雷：近距離攻撃
        // 雷の攻撃処理
        break;

    case 3:
        // 隕石：必殺技
        // 隕石の攻撃処理
        break;

    case 4:
        // 足場生成
        // 足場を生成する処理
        break;

    case 5:
        // 時間停止
        // 時間停止処理
        break;
    }
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

void RequestFireSkill(int life, VECTOR pos, VECTOR move, int Fire, int Water, int Thunder)
{
	FireSkill(life, pos, move, Fire, Water, Thunder);
}