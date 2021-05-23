#include "DXUT.h"
#include "stdafx.h"

void TestScene::Init()
{
	camera = new GameObject();
	camera->transform->position = { 0,40,-200 };
	camera->AddComponent<Camera>();
	camera->AddComponent<Light>();

	for (int i = 0; i < 8; i++)
	{
		auto kObj = new GameObject();
		kObj->AddComponent<MeshRenderer>();
		kObj->GetComponent<MeshRenderer>().SetXFile(L"Dolphin" + to_wstring((i % 3) + 1) + L".x");
		kObj->transform->position = { 100 * ((float)i), 40, 0 };
		kObj->transform->rotation.y = 45 * i;
		kObj->transform->scale = { 0.2,0.2,0.2 };
		Hierarchy.push_back(kObj);
	}

	//ground = new GameObject();
	//ground->AddComponent<Terrain>();
	//ground->GetComponent<Terrain>().spacing = 7;
	//ground->GetComponent<Terrain>().height = 200;
	//ground->GetComponent<Terrain>().SetGround(L"res/map210.bmp");

	Hierarchy.push_back(camera);
	//Hierarchy.push_back(ground);
}

void TestScene::Update()
{
	Scene::Update();

	if (DXUTWasKeyPressed('P'))
		SceneManager::GetInstance()->ChangeScene(L"CatScene");
}

void TestScene::Render()
{
	Scene::Render();	
}

void TestScene::Free()
{
	Scene::Free();
}
