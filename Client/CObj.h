#pragma once
#include "CEntity.h"

#include "CCamera.h"

class CCollider;
class CAnimator;

class CObj :
    public CEntity
{
private:
    Vec2   m_vPos;
    Vec2   m_vScale;

    CCollider*  m_pCollider;
    CAnimator* m_pAnimator;

    bool        m_bDead;

public:
    void SetPos(Vec2 _v) { m_vPos = _v; }
    Vec2 GetPos() { return m_vPos; }

    void SetScale(Vec2 _v) { m_vScale = _v; }
    Vec2 GetScale() { return m_vScale; }

    void CreateCollider();

    CCollider* GetCollider() { return m_pCollider; }
    


public:
    virtual void tick();
    virtual void render(HDC _dc);

    virtual void BeginOverlap(CCollider* _pOther) {}
    virtual void OnOverlap(CCollider* _pOther) {}
    virtual void EndOverlap(CCollider* _pOther) {}

    virtual LAYER returnLayer() = 0;
    virtual CObj* GetPointer() { return this; }

public:
    bool    IsDead() { return m_bDead; }
    void    SetDead();
    void    Instantiate(CObj* _pNewObj, Vec2 _vPos, LAYER _eLayer);

public:
    CObj();
    virtual ~CObj();

    friend class CEventMgr;
};

