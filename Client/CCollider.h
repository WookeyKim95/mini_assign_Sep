#pragma once
#include "CComponent.h"


class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos; // 어긋나는 것을 보완해주는 변수
    Vec2    m_vFinalPos; // offset이 적용된 포지션
    Vec2    m_vScale; // 콜리더의 크기
    int    m_iOverlapCount; // 겹쳐있었는가? 몇개랑?

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }

    Vec2 GetFinalPos() { return m_vFinalPos; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void BeginOverlap(CCollider* _pOther);
    void EndOverlap(CCollider* _pOther);
    void OnOverlap(CCollider* _pOther);


public:
    CCollider(CObj* _pOwner);
    ~CCollider();
};

