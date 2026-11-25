#include "DxLib.h"
#include "Slime.h"


SlimeData g_SlimeData = { 0 };

void InitSlime()
{
	g_SlimeData.move.x = 0.0f;
	g_SlimeData.move.y = 0.0f;
	g_SlimeData.active = false;
	g_SlimeData.slimeAnim = SLIME_ANIM_NONE;

	for (int i = 0; i < SLIME_ANIM_MAX; i++)
	{
		InitAnimation(&g_SlimeData.animation[i]);
	}
}

void LoadSlime()
{
	g_SlimeData.animation[SLIME_ANIM_IDLE].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_idle.png");
	g_SlimeData.animation[SLIME_ANIM_RUN].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_run.png");
	g_SlimeData.animation[SLIME_ANIM_DIE].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_die.png");
}

void StartSlime()
{

}

void StepSlime()
{

}

void UpdateSlime()
{

}

void DrawSlime()
{

}

void FinSlime()
{

}

SlimeData GetSlime()
{
	return g_SlimeData;
}