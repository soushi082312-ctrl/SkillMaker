#pragma once

enum BackGroundLayer
{
	BACK_GROUND_LAYER_1,
	BACK_GROUND_LAYER_2,
	BACK_GROUND_LAYER_3,
	BACK_GROUND_LAYER_MAX,
};

void InitBackGround();
void LoadBackGround(const char* path, BackGroundLayer layer);
void StepBackGround();
void UpdateBackGround();
void DrawBackGround();
void FinBackGround();

void SetBackGroundMove(float moveX, float moveY, BackGroundLayer layer);
