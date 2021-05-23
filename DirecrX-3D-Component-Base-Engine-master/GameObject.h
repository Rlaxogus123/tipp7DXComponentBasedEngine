#pragma once
#include "Transform.h"

class Component;
class GameObject :
	public Base
{
private:
	bool IsActive = true;
public:
	string name;
	Transform* transform;
	vector<Component*> inspector;

	GameObject();
	~GameObject() {};

	void SetActive(bool active) { IsActive = active; };
	bool activeSelf() { return IsActive ? true : false; };

	template<typename T>
	T& AddComponent();
	template<typename T>
	T& GetComponent();

	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();

	void Free() override;
};

template<typename T>
inline T& GameObject::AddComponent() // ������Ʈ �߰�
{
	T* pTransform = new T(); // �߰��Ϸ��� ������Ʈ Ÿ�� ���� �ϳ� ����
	Component* pComponent = static_cast<Component*>(pTransform); // �ش� ���� ������Ʈ�� ���� �ٿ�ĳ����

	pComponent->SetTransform(*this); // �ش� ������Ʈ�� �θ� Ʈ������ ����
	pComponent->Init(); // ������Ʈ Init����

	inspector.push_back(pComponent); // ������Ʈ ����Ʈ�� �߰�
	return *static_cast<T*>(pTransform); // ������Ʈ Ÿ�� �ּ� ��ȯ
}

template<typename T>
inline T& GameObject::GetComponent()
{
	for (int i = 0; i < inspector.size(); i++) // ��� �ν����� �˻�
	{
		if (dynamic_cast<T*>(inspector[i]) != nullptr) // ������Ʈ�� Ÿ�� ������Ʈ�� ���� ��ĳ����.. �����ϸ�
			return *static_cast<T*>(inspector[i]); // �ش� ������Ʈ�� �ּҸ� ��ȯ
	}
}
