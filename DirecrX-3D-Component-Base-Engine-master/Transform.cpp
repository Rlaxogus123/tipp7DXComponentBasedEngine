#include "DXUT.h"
#include "stdafx.h"
#include "Transform.h"

void Transform::Update()
{
	worldTOMatrix = GetWorldMatrix(position, rotation, scale);
}

Transform::Transform()
	:position(Vector3(0, 0, 0)), rotation(Vector3(0, 0, 0)), scale(Vector3(1, 1, 1))
{
	worldTOMatrix = GetWorldMatrix(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
}

Transform::Transform(Vector3& pos)
	: position(pos), rotation(Vector3(0, 0, 0)), scale(Vector3(1, 1, 1))
{
	worldTOMatrix = GetWorldMatrix(pos, Vector3(0, 0, 0), Vector3(1, 1, 1));
}

Transform::Transform(Vector3& pos, Vector3& rot)
	: position(pos), rotation(rot), scale(Vector3(1, 1, 1))
{
	worldTOMatrix = GetWorldMatrix(pos, rot, Vector3(1, 1, 1));
}

Transform::Transform(Vector3& pos, Vector3& rot, Vector3& scale_)
	: position(pos), rotation(rot), scale(scale_)
{
	worldTOMatrix = GetWorldMatrix(pos, rot, scale_);
}

MATRIX& Transform::GetWorldMatrix(const Vector3& pos, const Vector3& rot, const Vector3& scale_)const
{
	Vector3 position(pos);
	MATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);

	Vector3 Rotation(rot);

	MATRIX matrixx;
	D3DXMatrixRotationX(&matrixx, D3DXToRadian(Rotation.x));

	MATRIX matrixy;
	D3DXMatrixRotationY(&matrixy, D3DXToRadian(Rotation.y));

	MATRIX matrixz;
	D3DXMatrixRotationZ(&matrixz, D3DXToRadian(Rotation.z));

	MATRIX RotationEulerAngle = matrixz * matrixx * matrixy;


	Vector3 Scale(scale_);
	MATRIX mScale;
	D3DXMatrixScaling(&mScale, Scale.x, Scale.y, Scale.z);

	return mScale * RotationEulerAngle * mTranslate;
}

MATRIX& Transform::GetMatrix() const
{
	Vector3 Position(position);
	MATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, Position.x, Position.y, Position.z);

	Vector3 Rotation(rotation);
	MATRIX matrixx;
	D3DXMatrixRotationX(&matrixx, D3DXToRadian(Rotation.x));
	MATRIX matrixy;
	D3DXMatrixRotationY(&matrixy, D3DXToRadian(Rotation.y));
	MATRIX matrixz;
	D3DXMatrixRotationZ(&matrixz, D3DXToRadian(Rotation.z));

	MATRIX RotationEulerAngle = matrixz * matrixx * matrixy;

	Vector3 Scale(scale);
	MATRIX mScale;
	D3DXMatrixScaling(&mScale, Scale.x, Scale.y, Scale.z);

	return mScale * RotationEulerAngle * mTranslate;
}

void Transform::Free()
{
}
