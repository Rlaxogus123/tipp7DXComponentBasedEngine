#pragma once

class GameObject :
	public Base
{
private:
	bool IsActive = true;
public:
	string name;
	Transform* transform;
	std::vector<Component*> inspector;

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
inline T& GameObject::AddComponent()
{
	T* pTransform = new T();
	Component* pComponent = static_cast<Component*>(pTransform);

	pComponent->SetTransform(*this);
	pComponent->Init();

	inspector.push_back(pComponent);
	return *static_cast<T*>(pTransform);
}

template<typename T>
inline T& GameObject::GetComponent()
{
	for (int i = 0; i < inspector.size(); i++)
	{
		if (dynamic_cast<T*>(inspector[i]) != nullptr)
			return *static_cast<T*>(inspector[i]);
	}
}
