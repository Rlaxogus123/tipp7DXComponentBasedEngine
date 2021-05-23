#pragma once
class MeshRenderer :
    public Component
{
public:
	MeshRenderer();
    ~MeshRenderer();

	void Init() override;

	D3DXMATRIXA16 matWorld;
	LPD3DXMESH g_pMesh; // 메쉬 객체
	D3DMATERIAL9* g_pMeshMaterials; // 메쉬에 대한 재질
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // 메쉬에 대한 텍스쳐
	DWORD g_dwNumMaterials; // 재질의 수

	int SetXFile(wstring xFileName);
	int XFileDisplay();

    void Update() override;
    void Render() override;

	void Free() override;
};

