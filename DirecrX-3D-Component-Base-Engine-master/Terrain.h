#pragma once

class Terrain :
	public Component
{
public:
	Terrain();
	~Terrain();

	DWORD spacing; // 셀 간격
	DWORD height; // 높이 간격
	DWORD dwxHeight;
	DWORD dwzHeight;

	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPDIRECT3DINDEXBUFFER9 pIB;
	LPDIRECT3DTEXTURE9 g_pTexHeight = NULL; // 텍스쳐 높이맵
	LPDIRECT3DTEXTURE9 g_pTexDiffuse = NULL; // 텍스쳐 색깔맵
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

