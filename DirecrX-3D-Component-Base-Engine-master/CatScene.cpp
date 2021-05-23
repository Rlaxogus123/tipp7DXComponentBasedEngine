#include "DXUT.h"
#include "stdafx.h"
#include "MyMath.h"

void CatScene::Init()
{
	camera = new GameObject();
	camera->transform->position = { 150,40,-500 };
	camera->AddComponent<Camera>();
	camera->AddComponent<Light>();
	camera->AddComponent<Light>().vecDir = { 0,-10,0 };

	for (int i = 0; i < 4; ++i)
	{
		point[i] = new GameObject();
		point[i]->AddComponent<MeshRenderer>();
		point[i]->GetComponent<MeshRenderer>().SetXFile(L"Dolphin1.x");
		point[i]->transform->position = { 100 * ((float)i), (float)(rand() % 400)-200, 0 };
		point[i]->transform->rotation.y = -90;
		point[i]->transform->scale = { 0.1,0.1,0.1 };
		Hierarchy.push_back(point[i]);
	}

	object = new GameObject();
	object->AddComponent<MeshRenderer>();
	object->GetComponent<MeshRenderer>().SetXFile(L"Dolphin1.x");
	object->transform->position = { 0, 40, 0 };
	object->transform->rotation.y = -90;
	object->transform->scale = { 0.1,0.1,0.1 };

	Hierarchy.push_back(object);
	Hierarchy.push_back(camera);
}

void CatScene::Update()
{
	Scene::Update();

	amount += Time::detaTime;
	//myD3DXVec3CatmullRom(&object->transform->position,
	//	point[0]->transform->position,
	//	point[1]->transform->position,
	//	point[2]->transform->position,
	//	point[3]->transform->position,
	//	amount);
	D3DXVec3CatmullRom(&object->transform->position,
	&point[0]->transform->position,
	&point[1]->transform->position,
	&point[2]->transform->position,
	&point[3]->transform->position,
	amount);
	if (amount >= 2) amount = -1;

	if (DXUTWasKeyPressed('P'))
		SceneManager::GetInstance()->ChangeScene(L"TestScene");
}

void CatScene::Render()
{
	Scene::Render();
}

void CatScene::Free()
{
	Scene::Free();
}
