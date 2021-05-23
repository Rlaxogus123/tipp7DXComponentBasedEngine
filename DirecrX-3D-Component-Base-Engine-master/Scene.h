#pragma once
class Scene :
	public Base
{
public:
	Scene();
	virtual ~Scene();

	vector<GameObject*> Hierarchy;

	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Exit();

	void Free() override;
};

