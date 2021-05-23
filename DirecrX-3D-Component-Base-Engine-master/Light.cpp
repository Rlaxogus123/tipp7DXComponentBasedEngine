#include "DXUT.h"
#include "stdafx.h"

Light::Light()
{
}

Light::~Light()
{

}

void Light::Init()
{
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;

	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = Vector3(0, -10, 0);
}

void Light::Update()
{
}

void Light::Render()
{
	D3DXVec3Normalize((Vector3*)&light.Direction, &vecDir);

	DXUTGetD3D9Device()->SetLight(0, &light);
	DXUTGetD3D9Device()->LightEnable(0, TRUE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

void Light::Free()
{
}
