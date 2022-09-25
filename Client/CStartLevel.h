#pragma once
#include "CLevel.h"
class CStartLevel :
    public CLevel
{
public:
    virtual void init() override;

public:
    CStartLevel();
    ~CStartLevel();
};

