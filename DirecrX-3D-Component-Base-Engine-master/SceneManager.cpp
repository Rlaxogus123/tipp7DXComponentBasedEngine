#include "DXUT.h"
#include "SceneManager.h"

void SceneManager::AddScene(wstring _name, Scene* _scene)
{
	auto find = scenegroup.find(_name);
	if (find == scenegroup.end())
		scenegroup.emplace(_name, _scene);
}

void SceneManager::ChangeScene(wstring name)
{
	if (curScene != nullptr)
		curScene->Exit();
	if (scenegroup[name] != nullptr)
	{
		curScene = scenegroup[name];
		curScene->Init();
	}
	else cout << "CAN'T SCENE LOAD!! Please check Scene Name.";
}

void SceneManager::SceneUpdate()
{
	if (curScene != nullptr)
		curScene->Update();
}

void SceneManager::SceneFixedUpdate()
{
	if (curScene != nullptr)
		curScene->FixedUpdate();
}

void SceneManager::SceneRender()
{
	if (curScene != nullptr)
		curScene->Render();
}
