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
		if (n->activeSelf()) // ���ӿ�����Ʈ�� Ȱ��ȭ ��������
		{
			n->Update();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf()) // ���ӿ�����Ʈ�� Ȱ��ȭ ��������
		{
			n->FixedUpdate();
		}
	}
}

void Scene::Render()
{
	for (auto n : Hierarchy)
	{
		if (n->activeSelf()) // ���ӿ�����Ʈ�� Ȱ��ȭ ��������
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
			Safe_Release(n); // ��� ���ӿ�����Ʈ Free();
	}
	Hierarchy.clear();
}
