#pragma once
#include "stdafx.h"

class Transform;
class GameObject;
class Component :
	public Base
{
public:
	bool IsEnable = true;

	Transform* transform = nullptr;
	void SetTransform(GameObject& obj);

	GameObject* object = nullptr;
	GameObject* gameObject();

	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();

	void Free() override;
};

