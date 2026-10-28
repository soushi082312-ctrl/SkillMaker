#include "DxLib.h"
#include "Animation.h"

void InitAnimation(AnimationData* animData)
{
	animData->active = false;
	animData->handle = 0;
	animData->nowFrame = 0;
	animData->frameNum = 0;
	animData->frameWidth = 0;
	animData->frameHeight = 0;
	animData->timer = 0;
	animData->posX = 0.0f;
	animData->posY = 0.0f;
}

void StartAnimation(AnimationData* animData, float posX, float posY, int interval, int frameNum, int width, int height, bool isLoop)
{
	animData->active = true;

	animData->posX = posX;
	animData->posY = posY;

	animData->interval = interval;

	animData->timer = animData->interval;

	animData->nowFrame = 0;

	animData->frameNum = frameNum;

	animData->frameWidth = width;
	animData->frameHeight = height;

	animData->isLoop = isLoop;
}

void UpdateAnimation(AnimationData* animData)
{
	if (!animData->active) return;

	if (animData->timer <= 0)
	{
		animData->nowFrame++;
		animData->timer = animData->interval;

		if (animData->nowFrame >= animData->frameNum)
		{
			if (animData->isLoop)
			{
				animData->nowFrame = 0;
			}
			else
			{
				animData->active = false;
			}

			return;
		}
	}

	animData->timer--;
}

void DrawAnimation(AnimationData* animData, bool isTurnX, bool isTurnY)
{
	DrawAnimation(animData, animData->posX, animData->posY);
}

void DrawAnimation(AnimationData* animData, float posX, float posY, bool isTurnX, bool isTurnY)
{
	if (!animData->active)return;

	int frameX = animData->frameWidth * animData->nowFrame;

	DrawRectGraph((int)posX, (int)posY, frameX, 0, animData->frameWidth, animData->frameHeight, animData->handle, TRUE, isTurnX, isTurnY);
}