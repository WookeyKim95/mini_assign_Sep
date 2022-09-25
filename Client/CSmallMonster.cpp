#include "pch.h"
#include "CSmallMonster.h"

#include "CResMgr.h"
#include "CCollider.h"
#include "CTimeMgr.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CSmallMonster::CSmallMonster()
	: m_fSpeed(80.f)
	, m_HP(2)
	, m_pTexture(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(35.f, 35.f));

	// 이미지 로딩
	// m_pTexture = CResMgr::GetInst()->LoadTexture(L"SmallMonsterImg", L"texture\\Fighter.bmp");

	// 아하! 해결완료! 256색 비트맵으로 저장해야지 된다!
	m_pTexture = CResMgr::GetInst()->LoadTexture(L"SmallMonsterImg", L"texture\\scourge.bmp");
}

CSmallMonster::~CSmallMonster()
{
}

void CSmallMonster::tick()
{
	// 논리 연산 하는곳

	if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_pTarget->SetName(L"Player");
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * m_fSpeed * DT;
		vPos.y += vDir.y * m_fSpeed * DT;

		SetPos(vPos);
	}

	if (m_HP <= 0)
		SetDead();

	CObj::tick();
}

void CSmallMonster::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();

	// 원래 사각형
	/*HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);*/


	// 몬스터를 사진으로 그리기 시도 (실패, 원본 이미지 자체가 쓰기에 오류가 있는 듯.)
	// 해결완료! 256색 비트맵 이미지어야 잘 출력됨!

	Vec2 vLeftTop = Vec2(vPos.x - m_pTexture->Width() / 2.f, vPos.y - m_pTexture->Height() / 2.f);

	// 투명 쓰고 이미지 출력하기
	TransparentBlt(_dc, (int)vLeftTop.x, (int)vLeftTop.y
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, RGB(255, 0, 255));

	// 투명 안쓰고 이미지 출력하기
	/*BitBlt(_dc, (int)vLeftTop.x, (int)vLeftTop.y
		, (int)m_pTexture->Width(), (int)m_pTexture->Height()
		, m_pTexture->GetDC()
		, 0, 0
		, SRCCOPY);*/


	// 몬스터 HP 표시 구간.
	for (int i = 1; i <= m_HP; ++i)
	{
		HBRUSH hHPBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH hOrigin_HPBrush = (HBRUSH)SelectObject(_dc, hHPBrush);

		Rectangle(_dc, (int)(vPos.x - vSize.x / 3.f + 8.f * (float)i)
			, (int)(vPos.y - vSize.y)
			, (int)((vPos.x - vSize.x / 3.f + 8.f * (float)i + 5.f))
			, (int)(vPos.y - vSize.y + 5.f));

		SelectObject(_dc, hOrigin_HPBrush);
		DeleteObject(hHPBrush);
	}

	

	CObj::render(_dc);
}

LAYER CSmallMonster::returnLayer()
{
	return LAYER::MONSTER;
}

void CSmallMonster::BeginOverlap(CCollider* _pOther)
{
   	if (_pOther->GetOwner()->returnLayer() == LAYER::PLAYER_PROJECTILE)
		--m_HP;
}
