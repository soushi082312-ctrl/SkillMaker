#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Camera/Camera.h"

struct PlayerAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};
const PlayerAnimationParam PLAYER_ANIM_PARAM[PLAYER_ANIM_MAX] =
{
	8, 1, 90, 76,
	4, 8, 95, 76,
	8, 1, 50, 76,
	8, 1, 50, 76,
	8, 1, 95, 76,
    5, 10, 86, 76,
	5, 8, 95, 76
};

#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (786.0f)
#define PLAYER_MOVE_SPEED (4.0f)

#define PLAYER_JUMP_POWER (10.0f)
#define PLAYER_GRAVITY (0.4f)

#define PLAYER_MAP_COLLISION_OFFSET (0.05f)
#define PLAYER_BOX_COLLISION_OFFSET_X (24)
#define PLAYER_BOX_COLLISION_OFFSET_Y (20)
#define PLAYER_BOX_COLLISION_WIDTH (20)
#define PLAYER_BOX_COLLISION_HEIGHT (44)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };

void StartPlayerAnimation(PlayerAnimationType anim);	
void UpdatePlayerAnimation();
void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h);

void InitPlayer()
{
	g_PlayerData.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.pos.y = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.move.x = 0.0f;
	g_PlayerData.move.y = 0.0f;
	g_PlayerData.active = false;
	g_PlayerData.playAnim = PLAYER_ANIM_NONE;
	g_PlayerData.isAttack = false;
	g_PlayerData.isPose = false;
	g_PlayerData.attackTimer = 0;
	g_PlayerData.poseTimer = 0;

	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		InitAnimation(&g_PlayerData.animation[i]);
	}

	memset(&g_PlayerData.boxCollision, 0, sizeof(g_PlayerData.boxCollision));
}

void LoadPlayer()
{
	g_PlayerData.animation[PLAYER_ANIM_IDLE].handle = LoadGraph("Data/Player/Player_待機モーション.png");
	g_PlayerData.animation[PLAYER_ANIM_RUN].handle = LoadGraph("Data/Player/Player_移動モーション.png");
	g_PlayerData.animation[PLAYER_ANIM_JUMP].handle = LoadGraph("Data/Player/Player_ジャンプモーション.png");
	g_PlayerData.animation[PLAYER_ANIM_FALL].handle = LoadGraph("Data/Player/Player_落下モーション.png");
	g_PlayerData.animation[PLAYER_ANIM_LANDING].handle = LoadGraph("Data/Player/Player_着地モーション.png");
	g_PlayerData.animation[PLAYER_ANIM_ATTACK].handle = LoadGraph("Data/Player/Player_攻撃モーション.png");
	g_PlayerData.animation[PLAYER_ANIM_POSE].handle = LoadGraph("Data/Player/Player_スキルモーション.png");
}

void StartPlayer()
{
	g_PlayerData.active = true;

	g_PlayerData.boxCollision.pos.x = PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.pos.y = PLAYER_BOX_COLLISION_OFFSET_Y;
	g_PlayerData.boxCollision.width = PLAYER_BOX_COLLISION_WIDTH;
	g_PlayerData.boxCollision.height = PLAYER_BOX_COLLISION_HEIGHT;
	
	StartPlayerAnimation(PLAYER_ANIM_IDLE);
}

void StepPlayer()
{
	if (!g_PlayerData.active)
	{
		return;
	}

	g_PrevPlayerData = g_PlayerData;

	g_PlayerData.move.x = 0.0f;

	g_PlayerData.move.y += PLAYER_GRAVITY;

	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.move.x = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.move.x = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}

	if (IsTriggerKey(KEY_SPACE))
	{
		g_PlayerData.move.y = -PLAYER_JUMP_POWER;
	}

	if (IsTriggerKey(KEY_F) && !g_PlayerData.isAttack)
	{
		g_PlayerData.isAttack = true;
		g_PlayerData.attackTimer = 0;
		g_PlayerData.isTurn = false;

		StartPlayerAnimation(PLAYER_ANIM_ATTACK);
	}

	if (IsTriggerKey(KEY_S) && !g_PlayerData.isPose)
	{
		g_PlayerData.isPose = true;
		g_PlayerData.poseTimer = 0;
		g_PlayerData.isTurn = false;

		StartPlayerAnimation(PLAYER_ANIM_POSE);
	}
}

void UpdatePlayer()
{
	if (!g_PlayerData.active) return;

	if (g_PlayerData.move.y < 0.0f || g_PlayerData.move.y > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}

	if (g_PlayerData.isAttack)
	{
		g_PlayerData.attackTimer++;

		if (g_PlayerData.attackTimer >= 32)
		{
			g_PlayerData.isAttack = false;
			g_PlayerData.attackTimer = 0;
		}
	}

	if (g_PlayerData.isPose)
	{
		g_PlayerData.poseTimer++;
		if (g_PlayerData.poseTimer >= 32)
		{
			g_PlayerData.isPose = false;
			g_PlayerData.poseTimer = 0;
		}
	}

	g_PlayerData.pos.x += g_PlayerData.move.x;
	g_PlayerData.pos.y += g_PlayerData.move.y;

	UpdatePlayerAnimation();
}

void DrawPlayer()
{
	if (!g_PlayerData.active) return;

	CameraData camera = GetCamera();
	
	PlayerAnimationType animType = g_PlayerData.playAnim;  
	AnimationData* animData = &g_PlayerData.animation[animType];
	DrawAnimation(animData, g_PlayerData.pos.x - camera.pos.x, g_PlayerData.pos.y - camera.pos.y, g_PlayerData.isTurn);
}

void FinPlayer()
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		DeleteGraph(g_PlayerData.animation[i].handle);
	}
}

PlayerData GetPlayer()
{
	return g_PlayerData;
}

void PlayerHitNormalBlockX(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	player.isTurn = g_PrevPlayerData.isTurn;

	player.pos.x = g_PlayerData.pos.x;
	player.pos.y = g_PrevPlayerData.pos.y;

	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		if (player.move.x > 0.0f)
		{
			g_PlayerData.pos.x -= (x + w) - block->pos.x;
		}
		else if (player.move.x < 0.0f)
		{
			g_PlayerData.pos.x += (block->pos.x + MAP_CHIP_WIDTH) - x;
		}
	}
}

void PlayerHitNormalBlockY(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	player.isTurn = g_PrevPlayerData.isTurn;

	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		g_PlayerData.move.y = 0.0f;

		if (player.move.y > 0.0f)
		{
			g_PlayerData.pos.y -= (y + h) - block->pos.y;
			g_PlayerData.isAir = false;
		}
		else if (player.move.y < 0.0f)
		{
			g_PlayerData.pos.y += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
}

void StartPlayerAnimation(PlayerAnimationType anim)
{
	if (anim == g_PlayerData.playAnim) return;

	g_PlayerData.playAnim = anim;

	AnimationData* animData = &g_PlayerData.animation[anim];
	PlayerAnimationParam animParam = PLAYER_ANIM_PARAM[anim];

	StartAnimation(animData, g_PlayerData.pos.x, g_PlayerData.pos.y, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdatePlayerAnimation()
{
	if (g_PlayerData.isAttack)
	{
		PlayerAnimationType animType = g_PlayerData.playAnim;
		AnimationData* animData = &g_PlayerData.animation[animType];
		UpdateAnimation(animData);
		return;
	}

	if (g_PlayerData.isPose)
	{
		PlayerAnimationType animType = g_PlayerData.playAnim;
		AnimationData* animData = &g_PlayerData.animation[animType];
		UpdateAnimation(animData);
		return;
	}

	if (!g_PlayerData.isAir)
	{
		if (g_PlayerData.move.x != 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_RUN);
		}
		else
		{
			StartPlayerAnimation(PLAYER_ANIM_IDLE);
		}
	}
	else
	{
		if (g_PlayerData.move.y < 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_JUMP);
		}
		else if (g_PlayerData.move.y > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_FALL);
		}
	}

	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	UpdateAnimation(animData);
}

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h)
{
	x = player.isTurn ?
		player.pos.x + PLAYER_WIDTH - player.boxCollision.pos.x - player.boxCollision.width :
		player.pos.x + player.boxCollision.pos.x;
	y = player.pos.y + player.boxCollision.pos.y;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}
