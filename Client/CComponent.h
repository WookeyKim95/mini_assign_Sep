#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
private:
    CObj* const m_pOwner;

public:
    virtual void tick() = 0;
    virtual void render(HDC _dc) = 0;

public:
    CObj* GetOwner() { return m_pOwner; }

public:
    CComponent(CObj* _pOwner);
    ~CComponent();
};

