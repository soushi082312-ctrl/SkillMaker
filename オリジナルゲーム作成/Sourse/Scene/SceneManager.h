#pragma once

enum Scene
{
	SCENE_NONE,
	SCENE_PLAY,
};

enum SceneState
{
	SCENE_STATE_INIT,
	SCENE_STATE_LOAD,
	SCENE_STATE_START,
	SCENE_STATE_LOOP,
	SCENE_STATE_FIN,
};

void SceneManagerUpdate();

void InitScene();
void LoadScene();
void StartScene();
void StepScene();
void UpdateScene();
void DrawScene();
void FinScene();

void ChangeScene(Scene scene);