#include "DXUT.h"
#include "stdafx.h"

Camera::Camera()
{
}

void Camera::Init()
{
	D3DXVECTOR3 eye(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lookat(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matBill);
	CameraInit();
}

void Camera::CameraInit()
{
	D3DXVECTOR3 vEyePt = transform->position;
	D3DXVECTOR3 vLookatPt(transform->position.x, transform->position.y,0);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &matView);

	SetView(&vEyePt, &vLookatPt, &vUpVec);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 3, 1.0f, 1.0f, 5000.0f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

// 카메라 행렬을 생성하기위한 기본벡터값들 설정
D3DXMATRIXA16* Camera::SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp)
{
	transform->position = *pvEye;
	m_vLookat = *pvLookat;
	m_vUp = *pvUp;
	D3DXVec3Normalize(&m_vView, &(m_vLookat - transform->position));
	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);

	D3DXMatrixLookAtLH(&m_matView, &transform->position, &m_vLookat, &m_vUp);
	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);
	m_matBill._41 = 0;
	m_matBill._42 = 0;
	m_matBill._43 = 0;

	return &m_matView;
}

D3DXMATRIXA16* Camera::RotateLocalX(float angle)
{
	D3DXMATRIXA16 matRot; // 회전행렬
	D3DXMatrixRotationAxis(&matRot, &m_vCross, angle);
	D3DXVECTOR3 vNewDst; // 새롭게 볼 위치
	// view * rot으로 새로운 dst vector를 구한다
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot); // 회전행렬 * 시선벡터 = 새 위치벡터
	vNewDst += transform->position; // 실제 dst position = eyePosition + dst Vector;

	return SetView(&transform->position, &vNewDst, &m_vUp);
}

D3DXMATRIXA16* Camera::RotateLocalY(float angle)
{
	D3DXMATRIXA16 matRot; // 회전행렬
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);
	D3DXVECTOR3 vNewDst; // 새롭게 볼 위치
	// view * rot으로 새로운 dst vector를 구한다
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot); // 회전행렬 * 시선벡터 = 새 위치벡터
	vNewDst += transform->position; // 실제 dst position = eyePosition + dst Vector;

	return SetView(&transform->position, &vNewDst, &m_vUp);
}

D3DXMATRIXA16* Camera::RotateLocalZ(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);
	D3DXVECTOR3 vNewDst;
	// view * rot으로 새로운 dst vector를 구한다
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);
	vNewDst += transform->position; // 실제 dst position = eyePosition + dst Vector;

	return SetView(&transform->position, &vNewDst, &m_vUp);
}

D3DXMATRIXA16* Camera::MoveTo(D3DXVECTOR3* pv)
{
	return nullptr;
}

D3DXMATRIXA16* Camera::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = transform->position; // 새 위치
	D3DXVECTOR3 vNewLookat = m_vLookat; // 새 보는 곳

	D3DXVECTOR3 vMove; // 이동 가중치 벡터
	D3DXVec3Normalize(&vMove, &m_vCross); // 방향
	vMove *= dist; // 방향에 가중치를 곱함

	vNewEye += vMove; // 방향만큼 더해줌
	vNewLookat += vMove; // 방향만큼 더해줌
	return SetView(&vNewEye, &vNewLookat, &m_vUp);
}

D3DXMATRIXA16* Camera::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = transform->position; // 새 위치
	D3DXVECTOR3 vNewLookat = m_vLookat; // 새 보는 곳

	D3DXVECTOR3 vMove; // 이동 가중치 벡터
	D3DXVec3Normalize(&vMove, &m_vUp); // 방향
	vMove *= dist; // 방향에 가중치를 곱함

	vNewEye += vMove; // 방향만큼 더해줌
	vNewLookat += vMove; // 방향만큼 더해줌
	return SetView(&vNewEye, &vNewLookat, &m_vUp);
}

D3DXMATRIXA16* Camera::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = transform->position;
	D3DXVECTOR3 vNewLookat = m_vLookat;

	D3DXVECTOR3 vMove = m_vView;
	vMove *= dist;
	vNewEye += vMove;
	vNewLookat += vMove;
	return SetView(&vNewEye, &vNewLookat, &m_vUp);
}

void Camera::Update()
{
	if (DXUTIsKeyDown(VK_LEFT))
		RotateLocalY(D3DXToRadian(-1));
	if (DXUTIsKeyDown(VK_RIGHT))
		RotateLocalY(D3DXToRadian(1));
	if (DXUTIsKeyDown(VK_UP))
		RotateLocalX(D3DXToRadian(-1));
	if (DXUTIsKeyDown(VK_DOWN))
		RotateLocalX(D3DXToRadian(1));

	if (DXUTIsKeyDown(VK_SPACE))
		MoveLocalY(1);
	if (DXUTIsKeyDown(VK_LSHIFT))
		MoveLocalY(-1);

	if (DXUTIsKeyDown('A'))
		MoveLocalX(-1);
	if (DXUTIsKeyDown('D'))
		MoveLocalX(1);
	if (DXUTIsKeyDown('W'))
		MoveLocalZ(1);
	if (DXUTIsKeyDown('S'))
		MoveLocalZ(-1);
}

void Camera::Render()
{
	D3DXMATRIXA16* pmatView = GetViewMatrix();
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, pmatView);
	m_matBill._11 = pmatView->_11;
	m_matBill._13 = pmatView->_13;
	m_matBill._31 = pmatView->_31;
	m_matBill._33 = pmatView->_33;
}

void Camera::Free()
{
}

Camera::~Camera()
{
}
