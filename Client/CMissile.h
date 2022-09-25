#pragma once
#include "CObj.h"

class CMissile :
    public CObj
{
private:
    float   m_fSpeed;
    float   m_fDegree;
    float   m_fDistance;
    float   m_fMaxDistance;

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(float _fDegree) { m_fDegree = _fDegree; }
    void SetDistance(float _fDistance) { m_fDistance = _fDistance; }
    void SetMaxDistance(float _fMaxDistance) { m_fMaxDistance = _fMaxDistance; }
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual LAYER returnLayer() override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

