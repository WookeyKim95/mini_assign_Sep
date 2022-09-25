#pragma once
#include "CObj.h"

class CTexture;

class CSmallMonster :
    public CObj
{
public:

private:
    CTexture* m_pTexture;
    float   m_fSpeed;
    CObj* m_pTarget;
    int     m_HP;

private:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual LAYER returnLayer() override;

    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    void SetTarget(CObj* _pPlayer)
    {
        m_pTarget = _pPlayer;
    }
    void SetHP(int _HP) { m_HP = _HP; }
    int GetHP() { return m_HP; }

public:
    CSmallMonster();
    ~CSmallMonster();
};

