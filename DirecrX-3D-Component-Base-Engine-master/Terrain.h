#pragma once

class Terrain :
	public Component
{
public:
	Terrain();
	~Terrain();

	DWORD spacing; // �� ����
	DWORD height; // ���� ����
	DWORD dwxHeight;
	DWORD dwzHeight;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPDIRECT3DINDEXBUFFER9 pIB;
	LPDIRECT3DTEXTURE9 g_pTexHeight = NULL; // �ؽ��� ���̸�
	LPDIRECT3DTEXTURE9 g_pTexDiffuse = NULL; // �ؽ��� �����
	D3DXIMAGE_INFO g_pTexInfo;

	void Init() override;

	void SetGround(LPCWSTR path);
	void InitTexture(LPCWSTR path);
	void InitVB();
	void InitIB();
	
	void Update() override;
	void Render() override;

	void Free() override;
};

