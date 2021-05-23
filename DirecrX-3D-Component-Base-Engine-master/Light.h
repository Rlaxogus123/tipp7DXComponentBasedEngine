#pragma once
class Light :
	public Component
{
public:
	Light();
	~Light();

	void Init() override;

	D3DLIGHT9 light; // 조명
	Vector3 vecDir; // 조명의 방향

	void Update() override;
	void Render() override;

	void Free() override;
};

