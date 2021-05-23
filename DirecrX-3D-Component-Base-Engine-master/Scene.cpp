#include "DXUT.h"
#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}


void Scene::Init()
{
}

void Scene::Update()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf()) // 게임오브젝트가 활성화 되있으면
		{
			n->Update();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf()) // 게임오브젝트가 활성화 되있으면
		{
			n->FixedUpdate();
		}
	}
}

void Scene::Render()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf()) // 게임오브젝트가 활성화 되있으면
		{
			n->Render();
		}
	}
}

void Scene::Exit()
{
	Free();
}


void Scene::Free()
{
	for (auto& n : Hierarchy)
	{
		if (n != nullptr)
			Safe_Release(n); // 모든 게임오브젝트 Free();
	}
	Hierarchy.clear();
}
