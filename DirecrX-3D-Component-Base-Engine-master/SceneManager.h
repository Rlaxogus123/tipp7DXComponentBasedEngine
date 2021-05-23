#pragma once
#include "stdafx.h"
#include "Scene.h"

class SceneManager :
	public Singleton<SceneManager>
{
public:
	Scene* curScene = nullptr;
	map<wstring, Scene*> scenegroup;

	void AddScene(wstring _name, Scene* scene); // ¾À Ãß°¡
	void ChangeScene(wstring name); // ¾À ¹Ù²Ù±â 

	void SceneUpdate();
	void SceneFixedUpdate();
	void SceneRender();
};

