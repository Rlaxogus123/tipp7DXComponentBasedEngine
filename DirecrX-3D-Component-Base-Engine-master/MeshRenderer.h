#pragma once
class MeshRenderer :
    public Component
{
public:
	MeshRenderer();
    ~MeshRenderer();

	void Init() override;

	D3DXMATRIXA16 matWorld;
	LPD3DXMESH g_pMesh; // �޽� ��ü
	D3DMATERIAL9* g_pMeshMaterials; // �޽��� ���� ����
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // �޽��� ���� �ؽ���
	DWORD g_dwNumMaterials; // ������ ��

	int SetXFile(wstring xFileName);
	int XFileDisplay();

    void Update() override;
    void Render() override;

	void Free() override;
};

