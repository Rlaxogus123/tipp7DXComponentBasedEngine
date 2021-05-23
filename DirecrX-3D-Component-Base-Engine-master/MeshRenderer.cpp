#include "DXUT.h"
#include "stdafx.h"
#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer()
{
	
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Init()
{
	g_pMesh = NULL; // 메쉬 객체
	g_pMeshMaterials = NULL; // 메쉬에 대한 재질
	g_pMeshTextures = NULL; // 메쉬에 대한 텍스쳐
	g_dwNumMaterials = NULL; // 재질의 수
}


int MeshRenderer::XFileDisplay()
{
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient.r = mtrl.Ambient.r = mtrl.Ambient.r = mtrl.Ambient.r = 1.0f;
		mtrl.Diffuse.r = mtrl.Diffuse.r = mtrl.Diffuse.r = mtrl.Diffuse.r = 1.0f;
		mtrl.Specular.r = mtrl.Specular.r = mtrl.Specular.r = mtrl.Specular.r = 1.0f;
		mtrl.Emissive.r = mtrl.Emissive.r = mtrl.Emissive.r = mtrl.Emissive.r = 0.0f;
		mtrl.Power = 5.0f;

		DXUTGetD3D9Device()->SetMaterial(&g_pMeshMaterials[i]);
		DXUTGetD3D9Device()->SetTexture(0, g_pMeshTextures[i]);

		g_pMesh->DrawSubset(i);
	}

	DXUTGetD3D9Device()->SetTexture(0, NULL);
	return 0;
}

int MeshRenderer::SetXFile(wstring xFileName)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	auto route = L"res/" + xFileName;
	auto isFail = D3DXLoadMeshFromXW(route.c_str(), D3DXMESH_SYSTEMMEM, DXUTGetD3D9Device(), NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh);
	if (FAILED(isFail))
	{
		MessageBox(NULL, L"X파일 로드 실패", L"메쉬로드 실패", MB_OK);
		return E_FAIL;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			const CHAR* route = "res/";
			CHAR finalroute[MAX_PATH];
			sprintf(finalroute, "%s%s", route, d3dxMaterials[i].pTextureFilename);
	
			auto isFail = D3DXCreateTextureFromFileA(DXUTGetD3D9Device(), finalroute, &g_pMeshTextures[i]);
			if (FAILED(isFail))
			{
				g_pMeshTextures[i] = NULL;
				wcout << "TextureFail!! << " << finalroute << endl;
			}
			else
				wcout << "TextureLoad!! << " << finalroute << endl;
		}
	}

	pD3DXMtrlBuffer->Release();
	return 0;
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Render()
{
	matWorld = transform->GetMatrix();
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &matWorld);
	if(g_pMesh != NULL)
		XFileDisplay();
}

void MeshRenderer::Free()
{
	Safe_Release(g_pMesh);
	for (int i = 0; i < g_dwNumMaterials; i++)
	{
		delete &g_pMeshMaterials[i];
		Safe_Release(g_pMeshTextures[i]);
	}
	SAFE_DELETE_ARRAY(g_pMeshTextures);
}
