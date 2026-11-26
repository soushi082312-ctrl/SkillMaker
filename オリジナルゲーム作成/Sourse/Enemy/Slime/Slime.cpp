#include "DxLib.h"
#include "Slime.h"
#include "../../Collision/Collision.h"
#include "../../Camera/Camera.h"

struct SlimeAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};

const SlimeAnimationParam SLIME_ANIM_PARAM[SLIME_ANIM_MAX] =
{
	8, 4, 32, 32,
	8, 6, 32, 32,
	8, 5, 32, 32,
};

#define SLIME_DEFAULT_POS_X (400.0f)
#define SLIME_DEFAULT_POS_Y (824.0f)
#define SLIME_MOVE_SPEED (4.0f)

#define SLIME_GRAVITY (0.4f)

#define SLIME_MAP_COLLISION_OFFSET (0.05f)
#define SLIME_BOX_COLLISION_OFFSET_X (24)
#define SLIME_BOX_COLLISION_OFFSET_Y (20)
#define SLIME_BOX_COLLISION_WIDTH (20)
#define SLIME_BOX_COLLISION_HEIGHT (4)

SlimeData g_SlimeData = { 0 };
SlimeData g_PrevSlimeData = { 0 };

void StartSlimeAnimation(SlimeAnimationType anim);
void UpdateSlimeAnimation();
void CalcBoxCollision(SlimeData slime, float& x, float& y, float& w, float& h);

void InitSlime()
{
	g_SlimeData.pos.x = SLIME_DEFAULT_POS_X;
	g_SlimeData.pos.y = SLIME_DEFAULT_POS_Y;
	g_SlimeData.move.x = 0.0f;
	g_SlimeData.move.y = 0.0f;
	g_SlimeData.active = false;
	g_SlimeData.slimeAnim = SLIME_ANIM_NONE;

	for (int i = 0; i < SLIME_ANIM_MAX; i++)
	{
		InitAnimation(&g_SlimeData.animation[i]);
	}

	memset(&g_SlimeData.boxCollision, 0, sizeof(g_SlimeData.boxCollision));
}

void LoadSlime()
{
	g_SlimeData.animation[SLIME_ANIM_IDLE].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_idle.png");
	g_SlimeData.animation[SLIME_ANIM_RUN].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_run.png");
	g_SlimeData.animation[SLIME_ANIM_DIE].handle = LoadGraph("Data/Enemy/Slime/FreeSlime/slime_die.png");
}

void StartSlime()
{
	g_SlimeData.active = true;

	g_SlimeData.boxCollision.pos.x = SLIME_BOX_COLLISION_OFFSET_X;
	g_SlimeData.boxCollision.pos.y = SLIME_BOX_COLLISION_OFFSET_Y;
	g_SlimeData.boxCollision.width = SLIME_BOX_COLLISION_WIDTH;
	g_SlimeData.boxCollision.height = SLIME_BOX_COLLISION_HEIGHT;

	StartSlimeAnimation(SLIME_ANIM_IDLE);
}

void StepSlime()
{
	if (!g_SlimeData.active)
	{
		return;
	}

	g_PrevSlimeData = g_SlimeData;

	g_SlimeData.move.y += SLIME_GRAVITY;
}

void UpdateSlime()
{
	if (g_SlimeData.move.y < 0.0f || g_SlimeData.move.y > SLIME_GRAVITY)
	{
		g_SlimeData.isAir = true;
	}

	g_SlimeData.pos.x += g_SlimeData.move.x;
	g_SlimeData.pos.y += g_SlimeData.move.y;

	UpdateSlimeAnimation();
}

void DrawSlime()
{
	if (!g_SlimeData.active) return;

	CameraData camera = GetCamera();

	SlimeAnimationType animType = g_SlimeData.slimeAnim;
	AnimationData* animData = &g_SlimeData.animation[animType];
	DrawAnimation(animData, g_SlimeData.pos.x - camera.pos.x, g_SlimeData.pos.y - camera.pos.y, g_SlimeData.isTurn);
}

void FinSlime()
{
	for (int i = 0; i < SLIME_ANIM_MAX; i++)
	{
		DeleteGraph(g_SlimeData.animation[i].handle);
	}
}

SlimeData GetSlime()
{
	return g_SlimeData;
}

void SlimeHitNormalBlockX(MapChipData mapChipData)
{
	SlimeData slime = g_SlimeData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = SLIME_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = SLIME_MAP_COLLISION_OFFSET * 2;

	slime.isTurn = g_PrevSlimeData.isTurn;

	slime.pos.x = g_SlimeData.pos.x;
	slime.pos.y = g_PrevSlimeData.pos.y;

	float x, y, w, h;
	CalcBoxCollision(slime, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET, block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		if (slime.move.x > 0.0f)
		{
			g_SlimeData.pos.x -= (x + w) - block->pos.x;
		}
		else if (slime.move.x < 0.0f)
		{
			g_SlimeData.pos.x += (block->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}
}

void SlimeHitNormalBlockY(MapChipData mapChipData)
{
	SlimeData slime = g_SlimeData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = SLIME_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = SLIME_MAP_COLLISION_OFFSET * 2;

	slime.isTurn = g_PrevSlimeData.isTurn;

	float x, y, w, h;
	CalcBoxCollision(slime, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		g_SlimeData.move.y = 0.0f;

		if (slime.move.y > 0.0f)
		{
			g_SlimeData.pos.y -= (y + h) - block->pos.y;
			g_SlimeData.isAir = false;
		}
		else if (slime.move.y < 0.0f)
		{
			g_SlimeData.pos.y += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}

void StartSlimeAnimation(SlimeAnimationType anim)
{
	if (anim == g_SlimeData.slimeAnim) return;

	g_SlimeData.slimeAnim = anim;

	AnimationData* animData = &g_SlimeData.animation[anim];
	SlimeAnimationParam animParam = SLIME_ANIM_PARAM[anim];

	StartAnimation(animData, g_SlimeData.pos.x, g_SlimeData.pos.y, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdateSlimeAnimation()
{
	SlimeAnimationType animType = g_SlimeData.slimeAnim;
	AnimationData* animData = &g_SlimeData.animation[animType];
	UpdateAnimation(animData);
}

void CalcBoxCollision(SlimeData slime, float& x, float& y, float& w, float& h)
{
	x = slime.isTurn ?
		slime.pos.x + SLIME_WIDTH - slime.boxCollision.pos.x - slime.boxCollision.width :
		slime.pos.x + slime.boxCollision.pos.x;
	y = slime.pos.y + slime.boxCollision.pos.y;
	w = slime.boxCollision.width;
	h = slime.boxCollision.height;
}