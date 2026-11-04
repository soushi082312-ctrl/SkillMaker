#include "DxLib.h"
#include "Camera.h"
#include "../Input/Input.h"
#include "../Player/Player.h"

#define DEBUG_CAMERA_SPEED (4.0f)
#define CAMERA_SCROLL_SRART_X (200.0f)

CameraData g_CameraData = { 0 };

void InitCamera()
{
}

void StepCamera()
{
	PlayerData player = GetPlayer();

	if (player.pos.x >= CAMERA_SCROLL_SRART_X)
	{
		g_CameraData.pos.x = player.pos.x - CAMERA_SCROLL_SRART_X;
	}
	else
	{
		g_CameraData.pos.x = 0.0f;
	}
}

void DrawCamera()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カメラの座標＝[%f, %f]", g_CameraData.pos.x, g_CameraData.pos.y);
}

CameraData GetCamera()
{
	return g_CameraData;
}