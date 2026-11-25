#pragma once
#include "../../TestMap/MapParameter.h"
#include "../../Animation/Animation.h"

#define SLIME_WIDTH (40.0f)
#define SLIME_HEIGHT (32.0f)
#define SLIME_RADIUS (0.0f)

enum SlimeAnimationType
{
	SLIME_ANIM_IDLE,
	SLIME_ANIM_RUN,
	SLIME_ANIM_DIE,
	SLIME_ANIM_MAX, 
	SLIME_ANIM_NONE = -1
};

struct SlimeData
{
	bool active;
	bool isTurn;
	int hp;
	int handle;
	VECTOR pos;
	VECTOR move;
	AnimationData animation[SLIME_ANIM_MAX];
	SlimeAnimationType slimeAnim;
};

void InitSlime();
void LoadSlime();
void StartSlime();
void StepSlime();
void UpdateSlime();
void DrawSlime();
void FinSlime();

SlimeData GetSlime();