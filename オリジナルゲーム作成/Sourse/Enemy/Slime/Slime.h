#pragma once
#include "../../Animation/Animation.h"

#define SLIME_WIDTH (32)
#define SLIME_HEIGHT 

enum SlimeAnimationType
{
	SLIME_ANIM_IDLE,
	SLIME_ANIM_RUN,
	SLIME_ANIM_DIE,
};

struct SlimeData
{
	bool active;
	bool isTurn;
	int hp;
};

void InitSlime();
void LoadSlime();
void StartSlime();
void StepSlime();
void UpdateSlime();
void DrawSlime();
void FinSlime();

SlimeData GetSlime();