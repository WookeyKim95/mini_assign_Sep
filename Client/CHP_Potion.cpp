#include "pch.h"
#include "CHP_Potion.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CEventMgr.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"

#include "CCollider.h"

CHP_Potion::CHP_Potion()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	m_pTexture = CResMgr::GetInst()->LoadTexture(L"Potion", L"texture\\potion.bmp");
}

CHP_Potion::~CHP_Potion()
{
}

void CHP_Potion::tick()
{
	CObj::tick();
}

void CHP_Potion::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	// 원래 사각형 출력
	/*HBRUSH hHPBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOrigin_HPBrush = (HBRUSH)SelectObject(_dc, hHPBrush);

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOrigin_HPBrush);
	DeleteObject(hHPBrush);*/

	// 포션 이미지 출력
	Vec2 vLeftTop = Vec2(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	// 투명 쓰고 이미지 출력하기
	TransparentBlt(_dc, (int)vLeftTop.x, (int)vLeftTop.y
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, RGB(255, 0, 255));

	CObj::render(_dc);
}

void CHP_Potion::BeginOverlap(CCollider* _pOther)
{
}

LAYER CHP_Potion::returnLayer()
{
	return LAYER::ITEM;
}
