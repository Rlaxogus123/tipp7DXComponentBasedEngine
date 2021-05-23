#pragma once
#include "Component.h"

class Camera
	: public Component
{
	D3DXVECTOR3 m_vLookat; // ī�޶� ���� �ü���ġ
	D3DXVECTOR3 m_vUp; // ī�޶��� ��溤��
	D3DXVECTOR3 m_vView;// ī�޶� ���ϴ� �������⺤��	
	D3DXVECTOR3 m_vCross; // ī�޶��� ���麤��cross ( view,up )

	D3DXMATRIXA16 m_matView; // ī�޶� ���
	D3DXMATRIXA16 m_matBill; // ������ ��� (ī�޶��� �����)
public:
	Camera();
	~Camera();

	void Init() override;

	D3DXMATRIXA16* GetViewMatrix() { return &m_matView; };
	D3DXMATRIXA16* GetBillMatrix() { return &m_matBill; };

	// ī�޶������ �����ϱ� ���� �⺻���Ͱ����� �����ϴ� �Լ�
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);
	D3DXVECTOR3* GetView() { return &m_vView; };

	void SetLookat(D3DXVECTOR3* pv) { m_vLookat = *pv; };
	D3DXVECTOR3* GetLookat() { return &m_vLookat; };
	void SetUp(D3DXVECTOR3* pv) { m_vUp = *pv; };
	D3DXVECTOR3* GetUp() { return &m_vUp; };

	D3DXMATRIXA16* RotateLocalX(float angle);
	D3DXMATRIXA16* RotateLocalY(float angle);
	D3DXMATRIXA16* RotateLocalZ(float angle);
	D3DXMATRIXA16* MoveTo(D3DXVECTOR3* pv);
	D3DXMATRIXA16* MoveLocalX(float dist);
	D3DXMATRIXA16* MoveLocalY(float dist);
	D3DXMATRIXA16* MoveLocalZ(float dist);

	void CameraInit();
	void Update() override;
	void Render() override;
	
	void Free() override;
};

