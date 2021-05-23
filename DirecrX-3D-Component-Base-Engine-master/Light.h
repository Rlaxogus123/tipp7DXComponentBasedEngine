#pragma once
class Light :
	public Component
{
public:
	Light();
	~Light();

	void Init() override;

	D3DLIGHT9 light; // ����
	Vector3 vecDir; // ������ ����

	void Update() override;
	void Render() override;

	void Free() override;
};

