#pragma once
#include "../TestMap/MapParameter.h"
#include "../Animation/Animation.h"
#include "../Collision/Collision.h"


#define PLAYER_WIDTH	(43)
#define PLAYER_HEIGHT	(76)
#define PLAYER_RADIUS	(0)

enum PlayerAnimationType
{
	PLAYER_ANIM_IDLE,
	PLAYER_ANIM_RUN,
	PLAYER_ANIM_JUMP,
	PLAYER_ANIM_FALL,
	PLAYER_ANIM_LANDING,
	PLAYER_ANIM_ATTACK,
	PLAYER_ANIM_MAX,
	PLAYER_ANIM_NONE = -1
};

struct PlayerData
{
	bool active;
	bool isTurn;
	bool isAir;
	float posX;
	float posY;
	float moveX;
	float moveY;
	int handle;	
	AnimationData animation[PLAYER_ANIM_MAX];
	PlayerAnimationType playAnim;
	BoxCollision boxCollision;
};

void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

PlayerData GetPlayer();

void PlayerHitNormalBlockX(MapChipData mapChipData);
void PlayerHitNormalBlockY(MapChipData mapChipData);