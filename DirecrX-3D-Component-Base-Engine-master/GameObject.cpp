#include "DXUT.h"
#include "stdafx.h"

GameObject::GameObject()
{
	IsActive = true;
	transform = new Transform();
}

void GameObject::Update()
{
	for (auto n : inspector)
	{
		if (n->IsEnable)
		{
			n->Update();
		}
	}
}

void GameObject::FixedUpdate()
{
	for (auto n : inspector)
	{
		if (n->IsEnable)
		{
			n->FixedUpdate();
		}
	}
}

void GameObject::Render()
{
	for (auto n : inspector)
	{
		if (n->IsEnable)
		{
			n->Render();
		}
	}
}

void GameObject::Free()
{
	for (auto n : inspector)
	{
		Safe_Release(n);
	}
	inspector.clear();
}
