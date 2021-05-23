#include "DXUT.h"
#include "MyMath.h"

namespace MyMath
{
	void myD3DXVec3CatmullRom(Vector3* _out, Vector3 _p1, Vector3 _p2, Vector3 _p3, Vector3 _p4, float _time)
	{
		Vector3 slope1 = _p3 - _p1;
		Vector3 slope2 = _p4 - _p2;
		Vector3 a, b, c, d;

		D3DXMATRIX M = {
			0,0,0,1,
			1,1,1,1,
			0,0,1,0,
			3,2,1,0
		};
		D3DXMATRIX A = {
			_p2.x,_p2.y,_p2.z,0,
			_p3.x,_p3.y,_p3.z,0,
			slope1.x,slope1.y,slope1.z,0,
			slope2.x,slope2.y,slope2.z,0
		};
		D3DXMATRIX mOut;
		D3DXMatrixInverse(&M, NULL, &M);
		D3DXMatrixMultiply(&mOut, &M, &A);

		a.x = mOut._11;
		a.y = mOut._12;
		a.z = mOut._13;

		b.x = mOut._21;
		b.y = mOut._22;
		b.z = mOut._23;

		c.x = mOut._31;
		c.y = mOut._32;
		c.z = mOut._33;

		d.x = mOut._41;
		d.y = mOut._42;
		d.z = mOut._43;

		_out->x = a.x * pow(_time, 3) + b.x * pow(_time, 2) + (c.x * _time) + d.x;
		_out->y = a.y * pow(_time, 3) + b.y * pow(_time, 2) + (c.y * _time) + d.y;
		_out->z = a.z * pow(_time, 3) + b.z * pow(_time, 2) + (c.z * _time) + d.z;
	}
}