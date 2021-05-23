#pragma once
template<class T>
class Singleton
{
    static T* _Singleton;
public:
    static T* GetInstance()
    {
        if (nullptr == _Singleton)
        {
            _Singleton = new T;
        }
        return _Singleton;
    }
};

template<class T> T* Singleton<T>::_Singleton = nullptr;

template<typename T>
int Safe_Release(T& obj)
{
    DWORD refCount = 0;
    if (obj != NULL)
    {
        refCount = obj->Release(); // T->Release() 호출
        if (refCount == 0)
            obj = NULL;
    }
    return refCount;
}

struct CUSTOMVERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n; // 수직벡터 ( 빛 )
	D3DXVECTOR3 t; // 지면 텍스쳐 좌표
};
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE )

struct GROUNDVERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	DWORD Diffuse;
};

#define D3DFVF_GROUNDVERTEX ( D3DFVF_XYZ |  D3DFVF_NORMAL | D3DFVF_DIFFUSE )

struct MYINDEX {
	WORD _0, _1, _2; // WORD 16비트 인덱스
};

typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX MATRIX;

#define SCW 1280
#define SCH 720

using namespace std;

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "Base.h"
