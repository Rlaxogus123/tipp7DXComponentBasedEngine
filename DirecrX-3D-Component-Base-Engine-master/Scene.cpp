#include "DXUT.h"
#include "stdafx.h"

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
		if (n->activeSelf())
		{
			n->Update();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf())
		{
			n->FixedUpdate();
		}
	}
}

void Scene::Render()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf())
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
			Safe_Release(n);
	}
	Hierarchy.clear();
}
