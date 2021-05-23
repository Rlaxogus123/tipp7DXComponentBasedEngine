#include "DXUT.h"
#include "stdafx.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::Init()
{
	spacing = 1;
	g_pTexHeight = nullptr;
}

void Terrain::SetGround(LPCWSTR path)
{
	InitTexture(path);
	if (g_pTexHeight != nullptr)
	{
		InitVB();
		InitIB();
	}
}

void Terrain::InitTexture(LPCWSTR path)
{
	// 높이 맵
	if (FAILED(D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), path, D3DX_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, 0, &g_pTexInfo, NULL, &g_pTexHeight)))
	{
		cout << "Texture Load Fail! << " << path << endl;
		return;
	}
	// 색깔 맵
	if (FAILED(D3DXCreateTextureFromFile(DXUTGetD3D9Device(), L"tile2.tga", &g_pTexDiffuse)))
	{
		cout << "Diffuse Load Fail! << " << L"tile2.tga" << endl;
		return;
	}

	return;
}

void Terrain::InitVB()
{
	D3DSURFACE_DESC ddsd;
	D3DLOCKED_RECT LockRect;

	g_pTexHeight->GetLevelDesc(0, &ddsd);
	g_pTexHeight->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);
	dwxHeight = ddsd.Width;
	dwzHeight = ddsd.Height;
	int vertexCount = dwxHeight * dwzHeight;
	cout << "Texture Size : " << dwxHeight << "," << dwzHeight << endl;

	// 텍스처의 크기에 맞게 정점 버퍼를 생성한다.
	if (FAILED(DXUTGetD3D9Device()->CreateVertexBuffer(vertexCount * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, NULL))) {
		return;
	}

	// Lock() 함수를 통해 정점 버퍼에 정점을 저장할 수 있는 주소값을 얻는다.
	VOID* pVertexBuffer = nullptr;
	if (FAILED(pVB->Lock(0, vertexCount * sizeof(CUSTOMVERTEX), &pVertexBuffer, 0))) {
		return;
	}

	DWORD* pColor = (DWORD*)LockRect.pBits;
	CUSTOMVERTEX v;
	CUSTOMVERTEX* pV = new CUSTOMVERTEX[vertexCount];
	pV = (CUSTOMVERTEX*)pVertexBuffer;

	int index = 0;
	for (UINT z = 0; z < dwzHeight; ++z)
	{
		for (UINT x = 0; x < dwxHeight; ++x)
		{
			D3DXCOLOR color = pColor[index];
			float amount = (color.r + color.g + color.b) / 3;
	
			v.p.x = (float)(x - dwxHeight / 2.0f) * spacing;
			v.p.y = (float)(amount * height);
			v.p.z = -((float)(z - dwzHeight / 2.0f) * spacing);

			v.n.x = v.p.x;
			v.n.y = v.p.y * 10;
			v.n.z = v.p.z;
			D3DXVec3Normalize(&v.n, &v.n);
	
			index++;
			*pV++ = v;
		}
	}

	pVB->Unlock();
	g_pTexHeight->UnlockRect(0);

	return;
}

void Terrain::InitIB()
{
	if (FAILED(DXUTGetD3D9Device()->CreateIndexBuffer((dwxHeight - 1) * (dwzHeight - 1) * 2 * sizeof(MYINDEX),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL)))
	{
		return;
	}

	MYINDEX i;
	MYINDEX* pI;
	if (FAILED(pIB->Lock(0, (dwxHeight - 1) * (dwzHeight - 1) * 2 * sizeof(MYINDEX), (void**)&pI, 0)))
		return;

	for (DWORD z = 0; z < dwzHeight - 1; z++)
	{
		for (DWORD x = 0; x < dwxHeight - 1; x++)
		{
			// 왼쪽 위 삼각형
			i._0 = (z * dwxHeight + x);
			i._1 = (z * dwxHeight + x + 1);
			i._2 = ((z + 1) * dwxHeight + x);

			*pI++ = i;

			// 오른쪽 아래 삼각형
			i._0 = ((z + 1) * dwxHeight + x);
			i._1 = (z * dwxHeight + x + 1);
			i._2 = ((z + 1) * dwxHeight + x + 1);

			*pI++ = i;
		}
	}

	pIB->Unlock();

	return;
}

void Terrain::Update()
{
}

void Terrain::Render()
{
	if (g_pTexHeight == nullptr)
		return;

	DXUTGetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &transform->GetMatrix());
	DXUTGetD3D9Device()->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
	DXUTGetD3D9Device()->SetFVF(D3DFVF_CUSTOMVERTEX);
	DXUTGetD3D9Device()->SetIndices(pIB);
	DXUTGetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, dwxHeight * dwzHeight, 0, (dwxHeight - 1) * (dwzHeight - 1) * 2);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
}

void Terrain::Free()
{
	Safe_Release(pVB);
	Safe_Release(pIB);
	Safe_Release(g_pTexDiffuse);
	Safe_Release(g_pTexHeight);
}
