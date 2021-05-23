#pragma once
#include "Component.h"

class Camera
	: public Component
{
	D3DXVECTOR3 m_vLookat; // 카메라가 보는 시선위치
	D3DXVECTOR3 m_vUp; // 카메라의 상방벡터
	D3DXVECTOR3 m_vView;// 카메라가 향하는 단위방향벡터	
	D3DXVECTOR3 m_vCross; // 카메라의 측면벡터cross ( view,up )

	D3DXMATRIXA16 m_matView; // 카메라 행렬
	D3DXMATRIXA16 m_matBill; // 빌보드 행렬 (카메라의 역행렬)
public:
	Camera();
	~Camera();

	void Init() override;

	D3DXMATRIXA16* GetViewMatrix() { return &m_matView; };
	D3DXMATRIXA16* GetBillMatrix() { return &m_matBill; };

	// 카메라행렬을 생성하기 위한 기본벡터값들을 설정하는 함수
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

