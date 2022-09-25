#pragma once
#include "CEntity.h"


class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void AddObject(CObj* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }


public:
    CLevel();
    virtual ~CLevel();
};

