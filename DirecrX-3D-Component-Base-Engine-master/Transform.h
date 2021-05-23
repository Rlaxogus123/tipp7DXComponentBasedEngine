#pragma once
#include "Component.h"

class Transform :
    public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	MATRIX worldTOMatrix;

	virtual void Update();

	Transform();
	Transform(Vector3& position);
	Transform(Vector3& position, Vector3& rotation);
	Transform(Vector3& position, Vector3& rotation, Vector3& scale);

	MATRIX& GetWorldMatrix(const Vector3& pos, const Vector3& rot, const Vector3& scale_) const;
	MATRIX& GetMatrix() const;
	
	void Free() override;
};

