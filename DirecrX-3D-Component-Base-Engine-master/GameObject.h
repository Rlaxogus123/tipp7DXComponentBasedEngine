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
inline T& GameObject::AddComponent() // 컴포넌트 추가
{
	T* pTransform = new T(); // 추가하려는 컴포넌트 타입 변수 하나 생성
	Component* pComponent = static_cast<Component*>(pTransform); // 해당 변수 컴포넌트로 강제 다운캐스팅

	pComponent->SetTransform(*this); // 해당 컴포넌트의 부모 트랜스폼 설정
	pComponent->Init(); // 컴포넌트 Init실행

	inspector.push_back(pComponent); // 컴포넌트 리스트에 추가
	return *static_cast<T*>(pTransform); // 컴포넌트 타입 주소 반환
}

template<typename T>
inline T& GameObject::GetComponent()
{
	for (int i = 0; i < inspector.size(); i++) // 모든 인스펙터 검사
	{
		if (dynamic_cast<T*>(inspector[i]) != nullptr) // 컴포넌트를 타입 컴포넌트로 강제 업캐스팅.. 존재하면
			return *static_cast<T*>(inspector[i]); // 해당 컴포넌트의 주소를 반환
	}
}
