#pragma once

#include "CObj.h"

class CTexture;

class CHP_Potion :
    public CObj
{
private:
    CTexture* m_pTexture;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual LAYER returnLayer() override;

public:
    CHP_Potion();
    ~CHP_Potion();
};

