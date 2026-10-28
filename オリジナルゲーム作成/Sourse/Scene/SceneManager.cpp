#include "SceneManager.h"
#include "Play/PlayScene.h"

Scene g_NowScene = SCENE_PLAY;

SceneState g_SceneState = SCENE_STATE_INIT;

bool g_IsLoopEnd = false;

void SceneManagerUpdate()
{
	switch (g_SceneState)
	{
	case SCENE_STATE_INIT:
		InitScene();

		g_SceneState = SCENE_STATE_LOAD;
		break;

	case SCENE_STATE_LOAD:
		LoadScene();

		g_IsLoopEnd = false;

		g_SceneState = SCENE_STATE_START;
		break;

	case SCENE_STATE_START:
		StartScene();

		g_SceneState = SCENE_STATE_LOOP;
		break;

	case SCENE_STATE_LOOP:	
		StepScene();
		UpdateScene();
		DrawScene();

		if (g_IsLoopEnd)
		{
			g_SceneState = SCENE_STATE_FIN;
		}
		break;

	case SCENE_STATE_FIN:	
		FinScene();

		
		
		g_SceneState = SCENE_STATE_INIT;
		break;
	}
}

void InitScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		InitPlayScene();
		break;
	}
}

void LoadScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		LoadPlayScene();
		break;
	}
}

void StartScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		StartPlayScene();
		break;
	}
}

void StepScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		StepPlayScene();
		break;
	}
}

void UpdateScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		UpdatePlayScene();
		break;
	}
}

void DrawScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		DrawPlayScene();
		break;
	}
}

void FinScene()
{
	switch (g_NowScene)
	{
	case SCENE_PLAY:	
		FinPlayScene();
		break;
	}
}

void ChangeScene(Scene scene)
{
	g_IsLoopEnd = true;
}