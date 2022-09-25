#pragma once
#include "CObj.h"

class CMMissile :
    public CObj
{
private:
    float   m_fSpeed;
    Vec2    m_vDir;
    float   m_fDistance;
    float   m_fMaxDistance;
    CObj*   m_pTarget;

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }

    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() { return m_vDir; }

    void SetDistance(float _fDistance) { m_fDistance = _fDistance; }
    void SetMaxDistance(float _fMaxDistance) { m_fMaxDistance = _fMaxDistance; }

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual LAYER returnLayer() override;

    void SetTarget(CObj* _pPlayer)
    {
        m_pTarget = _pPlayer;
    }



public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CMMissile();
    ~CMMissile();
};