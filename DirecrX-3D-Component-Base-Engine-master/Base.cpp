#include "DXUT.h"
#include "Base.h"

int Base::AddReference()
{
    return refCount++;
}

int Base::Release()
{
    // ���� �����ϴ� ������ 0���̸�
    if (refCount == 0)
    {
        Free(); // �޸� ����
        delete this; // �����
        return 0;
    }
    return refCount--; // ���� 1�� ����
}
