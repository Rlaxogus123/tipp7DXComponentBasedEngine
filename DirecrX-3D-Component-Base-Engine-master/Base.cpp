#include "DXUT.h"
#include "Base.h"

int Base::AddReference()
{
    return refCount++;
}

int Base::Release()
{
    // 나를 참조하는 개수가 0개이면
    if (refCount == 0)
    {
        Free(); // 메모리 해제
        delete this; // 지우기
        return 0;
    }
    return refCount--; // 참조 1개 감소
}
