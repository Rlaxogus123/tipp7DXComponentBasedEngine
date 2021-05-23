#pragma once
#include "stdafx.h"
#include "Scene.h"

class SceneManager :
	public Singleton<SceneManager>
{
public:
	Scene* curScene = nullptr;
	map<wstring, Scene*> scenegroup;

	void AddScene(wstring _name, Scene* scene); // �� �߰�
	void ChangeScene(wstring name); // �� �ٲٱ� 

	void SceneUpdate();
	void SceneFixedUpdate();
	void SceneRender();
};

