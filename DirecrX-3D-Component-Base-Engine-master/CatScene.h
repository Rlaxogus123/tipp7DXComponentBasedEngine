#pragma once
#include "Scene.h"
class CatScene :
	public Scene
{
public:
	GameObject* camera;
	GameObject* object;
	GameObject* point[4];

	float amount = 0;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Free() override;
};

