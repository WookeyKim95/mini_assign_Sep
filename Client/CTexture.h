#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;

    BITMAP      m_tBitmapInfo;

public:

    UINT Width() { return m_tBitmapInfo.bmWidth; }
    UINT Height() { return m_tBitmapInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    CTexture();
    ~CTexture();
};

