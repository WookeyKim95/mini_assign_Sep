#pragma once
#include "CObj.h"

class CTexture;

class CMonster :
    public CObj
{
public:

private:
    CTexture* m_pTexture;

    float   m_fSpeed;
    int m_HP;
    float   m_CoolTime;
    float   m_MovingTime;
    int m_Dir;
    CObj* m_pTarget;

public:
    void    SetDir() { m_Dir = rand() % 360; };
    int    GetDir() { return m_Dir; }

    void SetTarget(CObj* _pPlayer)
    {
        m_pTarget = _pPlayer;
    }

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual LAYER returnLayer() override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    CMonster();
    ~CMonster();
};

