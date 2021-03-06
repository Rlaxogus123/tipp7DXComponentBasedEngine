#include "DXUT.h"
#include "Component.h"
#include "GameObject.h"

GameObject* Component::gameObject()
{
	if (object != nullptr)
		return object;
}

void Component::SetTransform(GameObject& obj)
{
	object = &obj;
	transform = obj.transform;
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::FixedUpdate()
{
}

void Component::Render()
{
}

void Component::Free()
{
}
