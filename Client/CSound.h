#pragma once
#include "CRes.h"
class CSound :
    public CRes
{
private:


private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    CSound();
    ~CSound();
};

