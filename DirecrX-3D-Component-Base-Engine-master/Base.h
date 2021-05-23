#pragma once
class Base
{
public:
	Base() {};
	virtual ~Base() {};
	virtual void Free() = 0;

	int refCount = 0;
	int AddReference();
	int Release();
};

