#pragma once
#include "CObj.h"

class CTexture;

enum class PLAYER_DIR
{
    PD_UP,
    PD_DOWN,
    PD_LEFT,
    PD_RIGHT,
    PD_END
};

class CPlayer :
    public CObj
{
private:
    CTexture* m_pTexture;
    CTexture* m_pTexture_L;
    CTexture* m_pTexture_D;
    CTexture* m_pTexture_R;

    float       m_fSpeed;
    PLAYER_DIR  CurDir;
    int     m_HP;
    int     m_MaxHP;
    int     m_boomCount;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
    virtual LAYER returnLayer() override;

    void    ImagePrint(CTexture* m_pTexture, HDC _dc, Vec2 Pos);

public:
    CPlayer();
    ~CPlayer();
};

