#pragma once
#include "CComponent.h"


class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos; // ��߳��� ���� �������ִ� ����
    Vec2    m_vFinalPos; // offset�� ����� ������
    Vec2    m_vScale; // �ݸ����� ũ��
    int    m_iOverlapCount; // �����־��°�? ���?

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }

    Vec2 GetFinalPos() { return m_vFinalPos; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void BeginOverlap(CCollider* _pOther);
    void EndOverlap(CCollider* _pOther);
    void OnOverlap(CCollider* _pOther);


public:
    CCollider(CObj* _pOwner);
    ~CCollider();
};

