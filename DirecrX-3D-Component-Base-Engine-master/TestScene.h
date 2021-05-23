#pragma once
#include "Scene.h"

class TestScene :
    public Scene
{
public:
	GameObject* ground;
	GameObject* camera;

    virtual void Init();
    virtual void Update();
    virtual void Render();

	void Free() override;
};

